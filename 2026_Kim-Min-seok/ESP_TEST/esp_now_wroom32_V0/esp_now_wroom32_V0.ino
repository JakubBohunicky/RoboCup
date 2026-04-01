#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

static const uint8_t S3_MAC[6] = {0x9c, 0x13, 0x9e, 0xac, 0x36, 0xdc};
static const uint8_t ESPNOW_CHANNEL = 1;

struct Soccer_MSG {
    uint8_t mode = 0;
    uint8_t role = 0;

    uint8_t drbF = 0;
    uint8_t drbR = 0;
    uint16_t ball_angle_ToNField = 0;
    uint16_t ball_distRaw = 0;

    uint8_t line_seen = 0;
    uint16_t gyro_offset_ToNField = 0;
    uint8_t goalEnemy_seen = 0;
};

Soccer_MSG txMsg = {};
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

    Serial.print("sizeof(Soccer_MSG) = ");
    Serial.println(sizeof(Soccer_MSG));

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
    txMsg.mode = 1;
    txMsg.role = 2;

    txMsg.drbF = 1;
    txMsg.drbR = 0;
    txMsg.ball_angle_ToNField = 123;
    txMsg.ball_distRaw = 456;

    txMsg.line_seen = 1;
    txMsg.gyro_offset_ToNField = 789;
    txMsg.goalEnemy_seen = 1;

    sendDone = false;

    esp_err_t result = esp_now_send(S3_MAC, (uint8_t*)&txMsg, sizeof(Soccer_MSG));
    if (result != ESP_OK) {
        Serial.printf("esp_now_send failed: %d\n", result);
        return;
    }

    Serial.print("Sent Soccer_MSG, size=");
    Serial.println(sizeof(Soccer_MSG));
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

    if (millis() - lastSend >= 500) {
        lastSend = millis();
        sendTestPacket();
    }

    if (sendDone) {
        sendDone = false;
        Serial.print("Send status: ");
        Serial.println(lastSendOk ? "OK" : "FAIL");
    }
}