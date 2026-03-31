#include "Low/Inputs/input_communication.h"
#include "robot_types.h"
#include "High/config_app.h"
#include "Low/config_hw.h"
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include <Arduino.h>


void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    IN::comms.lastSendOk = (status == ESP_NOW_SEND_SUCCESS);
    IN::comms.sendDone = true;
}

void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int len) {
    if (len != sizeof(_Raw::Comms_MSG)) return;

    memcpy(&IN::comms.rx_msg, data, sizeof(_Raw::Comms_MSG));
    IN::comms.lastRxMsg_ms = ST::now_ms;
    IN::comms.newRxPacket = true;
}


void input_comm_init_() {

    if (Robot_A) {
        for (uint8_t i = 0; i<6; i++) {
            IN::comms.PEER_MAC[i] = HW::Comms::MAC_B[i];
        }
    } else { 
        for (uint8_t i = 0; i<6; i++) {
            IN::comms.PEER_MAC[i] = HW::Comms::MAC_A[i];
        }
    }

    IN::comms.initialized = true;

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    esp_wifi_set_channel(HW::Comms::ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);

    Serial.print("ESP32 STA MAC Address: ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW init failed");
        IN::comms.initialized = false;
    }

     if (esp_now_register_send_cb(onDataSent) != ESP_OK) {
        Serial.println("Send callback register failed");
        IN::comms.initialized = false;
    }

    if (esp_now_register_recv_cb(onDataRecv) != ESP_OK) {
        Serial.println("Recv callback register failed");
        IN::comms.initialized = false;
    }

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, IN::comms.PEER_MAC, 6);
    peerInfo.channel = HW::Comms::ESPNOW_CHANNEL;
    peerInfo.ifidx = WIFI_IF_STA;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        IN::comms.initialized = false;
    }

    Serial.println("ESP-NOW ready");
}

bool sendState(uint8_t robotId, uint8_t mode, bool hasBall, bool seesBall) {
    IN::comms.tx_msg.version = 1;
    IN::comms.tx_msg.robotId = robotId;
    IN::comms.tx_msg.mode = mode;
    IN::comms.tx_msg.hasBall = hasBall ? 1 : 0;
    IN::comms.tx_msg.seq = IN::comms.txSeq++;
    IN::comms.tx_msg.uptimeMs = millis();
    IN::comms.tx_msg.seesBall = seesBall ? 1 : 0;

    IN::comms.sendDone = false;

    esp_err_t result = esp_now_send(IN::comms.PEER_MAC, (uint8_t*)& IN::comms.tx_msg, sizeof( IN::comms.tx_msg));
    if (result != ESP_OK) {
        Serial.printf("esp_now_send error: %d\n", result);
        return false;
    }

    return true;
}

void input_comm_update() {
    sendState(1, 2, false, true); // robotId, mode, hasBall, seesBall

     if ( IN::comms.newRxPacket) {
        IN::comms.newRxPacket = false;
        IN::comms.newRxPacket = ST::now_ms;

        Serial.printf("RX robot=%u mode=%u hasBall=%u seq=%lu\n",
                      IN::comms.rx_msg.robotId,
                      IN::comms.rx_msg.mode,
                      IN::comms.rx_msg.hasBall,
                      (unsigned long)IN::comms.rx_msg.seq);
    }

    if (ST::now_ms - IN::comms.lastRxMsg_ms <= 800) {
        IN::comms.online = true;
    } else IN::comms.online = false;
}


