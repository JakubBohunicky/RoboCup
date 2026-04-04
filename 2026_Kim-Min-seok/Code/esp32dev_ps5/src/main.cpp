#include <Arduino.h>
// #include <WiFi.h>
// #include <esp_wifi.h>
// #include <esp_now.h>
#include <ps5Controller.h>
#include <Wire.h>

struct __attribute__((packed)) ControllerTx_MSG {
    uint8_t connected = 0;
    uint32_t seq = 0;

    uint8_t right = 0;
    uint8_t down = 0;
    uint8_t up = 0;
    uint8_t left = 0;

    uint8_t square = 0;
    uint8_t cross = 0;
    uint8_t circle = 0;
    uint8_t triangle = 0;

    uint8_t l1 = 0;
    uint8_t r1 = 0;
    uint8_t l3 = 0;
    uint8_t r3 = 0;

    uint8_t share = 0;
    uint8_t options = 0;
    uint8_t psButton = 0;
    uint8_t touchpad = 0;

    uint8_t l2Pressed = 0;
    uint8_t r2Pressed = 0;

    int16_t l2 = 0;
    int16_t r2 = 0;
    int16_t lStickX = 0;
    int16_t lStickY = 0;
    int16_t rStickX = 0;
    int16_t rStickY = 0;
};

struct __attribute__((packed)) ControllerRx_MSG {
    uint8_t ledR = 0;
    uint8_t ledG = 0;
    uint8_t ledB = 0;

    uint32_t seq = 0;
    uint32_t uptimeMs = 0;

    uint8_t rumbleLeft = 0;
    uint8_t rumbleRight = 0;
    uint8_t flashOn = 0;
    uint8_t flashOff = 0;
};

volatile ControllerTx_MSG tx_controller_msg = {};
static volatile bool sendDone = false;
static volatile bool lastSendOk = false;

static ControllerRx_MSG isr_rx_controller_msg = {};
static ControllerRx_MSG rx_controller_msg = {};
static volatile bool newControllerRxPacket = false;

constexpr uint8_t CONTROLLER_PEER_MAC[6] = {0x9C, 0x13, 0x9E, 0xAC, 0x36, 0xDC};
                                         // 9C:13:9E:AC:36:DC
constexpr int ESPNOW_CHANNEL = 1;

uint32_t ps5_lastSendTime = 0;

uint32_t now_ms = 0;
uint32_t lastControllerRxMsg_ms = 0;
bool onlineController = false;

// static bool mac_equal(const uint8_t* a, const uint8_t* b) {
//     for (uint8_t i = 0; i < 6; i++) {
//         if (a[i] != b[i]) return false;
//     }
//     return true;
// }

// void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//     lastSendOk = (status == ESP_NOW_SEND_SUCCESS);
//     sendDone = true;
// }

// void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int len) {
//             Serial.println("Recieved1");  
//     if (!mac_equal(mac_addr, CONTROLLER_PEER_MAC)) return;
//             Serial.println("Recieved2");
//     if (len != sizeof(ControllerRx_MSG)) return;
//         Serial.println("Recieved3");
//     memcpy((void*)&isr_rx_controller_msg, data, sizeof(ControllerRx_MSG));
//     newControllerRxPacket = true;

//     Serial.printf(
//     "RX led=[%u,%u,%u] rumble=[%u,%u] flash=[%u,%u] seq=%lu up=%lu\n",
//     rx_controller_msg.ledR,
//     rx_controller_msg.ledG,
//     rx_controller_msg.ledB,
//     rx_controller_msg.rumbleLeft,
//     rx_controller_msg.rumbleRight,
//     rx_controller_msg.flashOn,
//     rx_controller_msg.flashOff,
//     (unsigned long)rx_controller_msg.seq,
//     (unsigned long)rx_controller_msg.uptimeMs
// );
// }

// static bool add_peer(const uint8_t mac[6]) {
//     if (esp_now_is_peer_exist(mac)) return true;

//     esp_now_peer_info_t peerInfo = {};
//     memcpy(peerInfo.peer_addr, mac, 6);
//     peerInfo.channel = ESPNOW_CHANNEL;
//     peerInfo.ifidx = WIFI_IF_STA;
//     peerInfo.encrypt = false;

//     return esp_now_add_peer(&peerInfo) == ESP_OK;
// }

static void fill_controller_message() {
    // tx_controller_msg.version = 1;
    tx_controller_msg.connected = ps5.isConnected() ? 1 : 0;
    tx_controller_msg.seq++;
    // tx_controller_msg.uptimeMs = now_ms;

    tx_controller_msg.right = ps5.Right();
    tx_controller_msg.down = ps5.Down();
    tx_controller_msg.up = ps5.Up();
    tx_controller_msg.left = ps5.Left();

    tx_controller_msg.square = ps5.Square();
    tx_controller_msg.cross = ps5.Cross();
    tx_controller_msg.circle = ps5.Circle();
    tx_controller_msg.triangle = ps5.Triangle();

    tx_controller_msg.l1 = ps5.L1();
    tx_controller_msg.r1 = ps5.R1();
    tx_controller_msg.l3 = ps5.L3();
    tx_controller_msg.r3 = ps5.R3();

    tx_controller_msg.share = ps5.Share();
    tx_controller_msg.options = ps5.Options();
    tx_controller_msg.psButton = ps5.PSButton();
    tx_controller_msg.touchpad = ps5.Touchpad();

    tx_controller_msg.l2Pressed = ps5.L2();
    tx_controller_msg.r2Pressed = ps5.R2();

    tx_controller_msg.l2 = ps5.L2Value();
    tx_controller_msg.r2 = ps5.R2Value();
    tx_controller_msg.lStickX = ps5.LStickX();
    tx_controller_msg.lStickY = ps5.LStickY();
    tx_controller_msg.rStickX = ps5.RStickX();
    tx_controller_msg.rStickY = ps5.RStickY();
}

// static void process_rx_feedback() {
//     if (newControllerRxPacket) {
//         newControllerRxPacket = false;
//         memcpy(&rx_controller_msg, (const void*)&isr_rx_controller_msg, sizeof(ControllerRx_MSG));
//         lastControllerRxMsg_ms = now_ms;

//         if (ps5.isConnected()) {
//             ps5.setLed(
//                 rx_controller_msg.ledR,
//                 rx_controller_msg.ledG,
//                 rx_controller_msg.ledB
//             );

//             ps5.setFlashRate(
//                 rx_controller_msg.flashOn,
//                 rx_controller_msg.flashOff
//             );

//             ps5.setRumble(
//                 rx_controller_msg.rumbleLeft,
//                 rx_controller_msg.rumbleRight
//             );

//             ps5.sendToController();
//         }
//     }

//     if (now_ms - lastControllerRxMsg_ms <= 100) {
//         onlineController = true;
//     } else {
//         onlineController = false;
//     }
// }


constexpr uint8_t I2C_ADDR = 0x42;
constexpr int SDA_PIN = 21;
constexpr int SCL_PIN = 22;

void onRequestI2C() {
    Wire.write((const uint8_t*)&tx_controller_msg, sizeof(tx_controller_msg));
}

void setup() {
    Serial.begin(921600);

    Wire.setBufferSize(128);
    Wire.onRequest(onRequestI2C);
    Wire.begin((uint8_t)I2C_ADDR, SDA_PIN, SCL_PIN, 1000000);

    // WiFi.mode(WIFI_STA);
    // WiFi.disconnect();
    // delay(100);
    // esp_wifi_set_channel(ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);

    // if (esp_now_init() != ESP_OK) {
    //     Serial.println("ESP-NOW init failed");
    //     while (true) delay(1000);
    // }

    // esp_now_register_send_cb(onDataSent);
    // esp_now_register_recv_cb(onDataRecv);

    // if (!add_peer(CONTROLLER_PEER_MAC)) {
    //     Serial.println("Failed to add controller peer");
    //     while (true) delay(1000);
    // }

    // Serial.print("ESP32 STA MAC: ");
    // Serial.println(WiFi.macAddress());

    ps5.begin("58:10:31:2f:f7:f0"); // MAC adresa tvojho PS5 ovladaca
    Serial.println("Ready.");
}

void loop() {
    now_ms = millis();

    fill_controller_message();
    // if(now_ms - ps5_lastSendTime >= 10) {
    //   process_rx_feedback();
    //   ps5_lastSendTime = now_ms;
    // }

    // if (ps5.isConnected()) {
    //     esp_now_send(CONTROLLER_PEER_MAC, (uint8_t*)&tx_controller_msg, sizeof(tx_controller_msg));
    //     // Serial.println("Sent");
    // }
 
    // delay(10); // ~100 Hz
}