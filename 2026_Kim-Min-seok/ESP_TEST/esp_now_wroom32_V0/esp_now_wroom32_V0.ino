#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

static const uint8_t S3_MAC[6] = {0x9c, 0x13, 0x9e, 0xac, 0x36, 0xdc}; // sem daj MAC S3
static const uint8_t ESPNOW_CHANNEL = 1;

struct RobotStateMsg {
    uint8_t version;
    uint8_t robotId;
    uint8_t mode;
    uint8_t hasBall;
    uint32_t seq;
    uint32_t uptimeMs;
    uint8_t seesBall;
    uint8_t reserved1;
    uint16_t reserved2;
};

RobotStateMsg txMsg = {};
uint32_t txSeq = 0;
volatile bool sendDone = false;
volatile bool lastSendOk = false;

void onDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
    lastSendOk = (status == ESP_NOW_SEND_SUCCESS);
    sendDone = true;
}

bool initEspNow() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);

    Serial.print("WROOM32 STA MAC: ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW init failed");
        return false;
    }

    if (esp_now_register_send_cb(onDataSent) != ESP_OK) {
        Serial.println("Register send callback failed");
        return false;
    }

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, S3_MAC, 6);
    peerInfo.channel = ESPNOW_CHANNEL;
    peerInfo.ifidx = WIFI_IF_STA;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Add peer failed");
        return false;
    }

    Serial.println("ESP-NOW sender ready");
    return true;
}

void sendTestPacket() {
    txMsg.version = 1;
    txMsg.robotId = 2;
    txMsg.mode = 1;
    txMsg.hasBall = (txSeq % 2);
    txMsg.seq = txSeq++;
    txMsg.uptimeMs = millis();
    txMsg.seesBall = 1;

    sendDone = false;

    esp_err_t result = esp_now_send(S3_MAC, (uint8_t*)&txMsg, sizeof(txMsg));
    if (result != ESP_OK) {
        Serial.printf("esp_now_send failed: %d\n", result);
        return;
    }

    Serial.print("Sent seq=");
    Serial.println(txMsg.seq);
}

void setup() {
    Serial.begin(115200);
    delay(500);

    if (!initEspNow()) {
        while (true) {
            delay(1000);
        }
    }
}

void loop() {
    static uint32_t lastSend = 0;

    if (millis() - lastSend >= 200) {
        lastSend = millis();
        sendTestPacket();
    }

    if (sendDone) {
        sendDone = false;
        Serial.print("Send status: ");
        Serial.println(lastSendOk ? "OK" : "FAIL");
    }
}