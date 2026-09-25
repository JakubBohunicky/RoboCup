// #include <Arduino.h>
// #include <ps5Controller.h>
// #include <Wire.h>


// struct __attribute__((packed)) ControllerTx_MSG {
//     uint16_t magicHead = 0xA55A;

//     uint8_t connected = 0;
//     uint32_t seq = 0;

//     uint8_t right = 0;
//     uint8_t down = 0;
//     uint8_t up = 0;
//     uint8_t left = 0;

//     uint8_t square = 0;
//     uint8_t cross = 0;
//     uint8_t circle = 0;
//     uint8_t triangle = 0;

//     uint8_t l1 = 0;
//     uint8_t r1 = 0;
//     uint8_t l3 = 0;
//     uint8_t r3 = 0;

//     uint8_t share = 0;
//     uint8_t options = 0;
//     uint8_t psButton = 0;
//     uint8_t touchpad = 0;

//     uint8_t l2Pressed = 0;
//     uint8_t r2Pressed = 0;

//     int16_t l2 = 0;
//     int16_t r2 = 0;
//     int16_t lStickX = 0;
//     int16_t lStickY = 0;
//     int16_t rStickX = 0;
//     int16_t rStickY = 0;

//     uint16_t magicTail = 0x55AA;
// };


// constexpr uint8_t ROBOT_I2C_ADDR = 0x42;
// constexpr int SDA_PIN = 21;
// constexpr int SCL_PIN = 22;
// constexpr uint32_t I2C_FREQ = 400000UL;


// ControllerTx_MSG tx_msg = {};


// static void fill_controller_message(ControllerTx_MSG& msg) {
//     msg.magicHead = 0xA55A;

//     msg.connected = ps5.isConnected() ? 1 : 0;

//     msg.right = ps5.Right();
//     msg.down = ps5.Down();
//     msg.up = ps5.Up();
//     msg.left = ps5.Left();

//     msg.square = ps5.Square();
//     msg.cross = ps5.Cross();
//     msg.circle = ps5.Circle();
//     msg.triangle = ps5.Triangle();

//     msg.l1 = ps5.L1();
//     msg.r1 = ps5.R1();
//     msg.l3 = ps5.L3();
//     msg.r3 = ps5.R3();

//     msg.share = ps5.Share();
//     msg.options = ps5.Options();
//     msg.psButton = ps5.PSButton();
//     msg.touchpad = ps5.Touchpad();

//     msg.l2Pressed = ps5.L2();
//     msg.r2Pressed = ps5.R2();

//     msg.l2 = ps5.L2Value();
//     msg.r2 = ps5.R2Value();
//     msg.lStickX = ps5.LStickX();
//     msg.lStickY = ps5.LStickY();
//     msg.rStickX = ps5.RStickX();
//     msg.rStickY = ps5.RStickY();

//     msg.magicTail = 0x55AA;
// }


// void setup() {
//     Serial.begin(921600);
//     delay(500);

//     // Master mode — žiadna adresa, len piny a frekvencia
//     Wire.begin(SDA_PIN, SCL_PIN);
//     Wire.setClock(I2C_FREQ);

//     ps5.begin("58:10:31:2f:f7:f0");

//     Serial.println("I2C master ready");
// }


// void loop() {
//     static uint32_t lastUpdate = 0;
//     static uint32_t lastPrint = 0;
//     static uint32_t seqCounter = 0;

//     if (millis() - lastUpdate >= 10) {
//         lastUpdate = millis();

//         tx_msg.seq = ++seqCounter;
//         fill_controller_message(tx_msg);

//         // Push dáta na robot — bez čakania na odpoveď
//         Wire.beginTransmission(ROBOT_I2C_ADDR);
//         Wire.write((uint8_t*)&tx_msg, sizeof(tx_msg));
//         uint8_t err = Wire.endTransmission();

//         if (err != 0) {
//             Serial.printf("I2C write error: %u\n", err);
//         }
//     }

//     if (millis() - lastPrint >= 500) {
//         lastPrint = millis();
//         Serial.printf(
//             "seq=%lu connected=%u LX=%d LY=%d RX=%d RY=%d size=%u\n",
//             (unsigned long)tx_msg.seq,
//             tx_msg.connected,
//             (int)tx_msg.lStickX,
//             (int)tx_msg.lStickY,
//             (int)tx_msg.rStickX,
//             (int)tx_msg.rStickY,
//             (unsigned)sizeof(ControllerTx_MSG)
//         );
//     }
// }