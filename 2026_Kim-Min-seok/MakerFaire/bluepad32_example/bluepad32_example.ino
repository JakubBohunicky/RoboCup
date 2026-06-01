#include <Arduino.h>
#include <Bluepad32.h>

struct __attribute__((packed)) ControllerTx_MSG {
    uint16_t magicHead = 0xA55A;
    uint8_t  connected = 0;
    uint32_t seq = 0;
    uint8_t right=0, down=0, up=0, left=0;
    uint8_t square=0, cross=0, circle=0, triangle=0;
    uint8_t l1=0, r1=0, l3=0, r3=0;
    uint8_t share=0, options=0, psButton=0, touchpad=0;
    uint8_t l2Pressed=0, r2Pressed=0;
    int16_t l2=0, r2=0;
    int16_t lStickX=0, lStickY=0;
    int16_t rStickX=0, rStickY=0;
    uint16_t magicTail = 0x55AA;
};

constexpr int UART_TX_PIN = 17;
constexpr int UART_BAUD   = 1000000;

ControllerTx_MSG tx_msg = {};
uint32_t seqCounter = 0;

ControllerPtr myController = nullptr;

void onConnectedController(ControllerPtr ctl) {
    myController = ctl;
    Serial.println("Controller connected!");
}

void onDisconnectedController(ControllerPtr ctl) {
    myController = nullptr;
    Serial.println("Controller disconnected!");
}

static void fill_msg(ControllerTx_MSG& m, ControllerPtr ctl) {
    m.magicHead = 0xA55A;
    m.connected = (ctl && ctl->isConnected()) ? 1 : 0;

    if (!m.connected) {
        // nuluj všetky hodnoty ak nie je pripojený
        m.right = m.down = m.up = m.left = 0;
        m.square = m.cross = m.circle = m.triangle = 0;
        m.l1 = m.r1 = m.l3 = m.r3 = 0;
        m.share = m.options = m.psButton = m.touchpad = 0;
        m.l2Pressed = m.r2Pressed = 0;
        m.l2 = m.r2 = 0;
        m.lStickX = m.lStickY = 0;
        m.rStickX = m.rStickY = 0;
        m.magicTail = 0x55AA;
        return;
    }

    uint8_t dpad    = ctl->dpad();
    uint16_t btns   = ctl->buttons();
    uint8_t misc    = ctl->miscButtons();

    // D-pad (bitmaska)
    m.up     = (dpad & 0x01) ? 1 : 0;
    m.down   = (dpad & 0x02) ? 1 : 0;
    m.right  = (dpad & 0x04) ? 1 : 0;
    m.left   = (dpad & 0x08) ? 1 : 0;

    // Tlačidlá – Bluepad32 mapuje PS5: cross=A, circle=B, square=X, triangle=Y
    m.cross    = (btns & 0x0001) ? 1 : 0;  // A / Cross
    m.circle   = (btns & 0x0002) ? 1 : 0;  // B / Circle
    m.square   = (btns & 0x0004) ? 1 : 0;  // X / Square
    m.triangle = (btns & 0x0008) ? 1 : 0;  // Y / Triangle
    m.l1       = (btns & 0x0010) ? 1 : 0;
    m.r1       = (btns & 0x0020) ? 1 : 0;
    m.l2Pressed= (btns & 0x0040) ? 1 : 0;
    m.r2Pressed= (btns & 0x0080) ? 1 : 0;
    m.l3       = (btns & 0x0400) ? 1 : 0;
    m.r3       = (btns & 0x0800) ? 1 : 0;

    // Misc tlačidlá (share, options, PS, touchpad)
    m.share    = (misc & 0x01) ? 1 : 0;
    m.options  = (misc & 0x02) ? 1 : 0;
    m.psButton = (misc & 0x08) ? 1 : 0;
    m.touchpad = (misc & 0x10) ? 1 : 0;

    // L2/R2 analógové hodnoty: Bluepad32 dáva 0–1023, stará knižnica dávala 0–255
    // Normalizujeme na int16_t (0–255 rozsah pre kompatibilitu)
    m.l2 = (int16_t)(ctl->brake()    >> 2);  // 0-1023 → 0-255
    m.r2 = (int16_t)(ctl->throttle() >> 2);  // 0-1023 → 0-255

    // Joysticky: Bluepad32 dáva -511..512, mapa na int16_t priamo
    m.lStickX = (int16_t)ctl->axisX();
    m.lStickY = (int16_t)ctl->axisY();
    m.rStickX = (int16_t)ctl->axisRX();
    m.rStickY = (int16_t)ctl->axisRY();

    m.magicTail = 0x55AA;
}


static void dump_msg(const ControllerTx_MSG& m) {
    Serial.printf("=== UART TX DUMP (seq=%lu) ===\n", m.seq);
    Serial.printf("  connected : %u\n", m.connected);
    Serial.printf("  D-pad     : UP=%u DN=%u LT=%u RT=%u\n", m.up, m.down, m.left, m.right);
    Serial.printf("  Buttons   : X=%u O=%u []=%u /\\=%u\n", m.cross, m.circle, m.square, m.triangle);
    Serial.printf("  Shoulder  : L1=%u R1=%u L2btn=%u R2btn=%u\n", m.l1, m.r1, m.l2Pressed, m.r2Pressed);
    Serial.printf("  Sticks    : L3=%u R3=%u\n", m.l3, m.r3);
    Serial.printf("  Misc      : Share=%u Opt=%u PS=%u Touch=%u\n", m.share, m.options, m.psButton, m.touchpad);
    Serial.printf("  L2/R2 val : L2=%d R2=%d\n", m.l2, m.r2);
    Serial.printf("  L stick   : X=%d Y=%d\n", m.lStickX, m.lStickY);
    Serial.printf("  R stick   : X=%d Y=%d\n", m.rStickX, m.rStickY);
    Serial.printf("  Magic     : HEAD=0x%04X TAIL=0x%04X\n", m.magicHead, m.magicTail);
    Serial.printf("  Raw bytes : ");
    const uint8_t* p = (const uint8_t*)&m;
    for (size_t i = 0; i < sizeof(m); i++) {
        Serial.printf("%02X ", p[i]);
    }
    Serial.println();
    Serial.println("==============================");
}


void setup() {
    Serial.begin(1000000 );
    Serial2.begin(UART_BAUD, SERIAL_8N1, -1, UART_TX_PIN);

    BP32.setup(&onConnectedController, &onDisconnectedController);
    BP32.forgetBluetoothKeys();  // odstráň ak chceš auto-reconnect

    Serial.println("Bluepad32 UART sender ready");
    Serial.printf("BD Addr: ");
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n",
        addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
}

void loop() {
    static uint32_t lastUpdate = 0;
    static uint32_t lastPrint  = 0;

    BP32.update();  // MUSÍ byť volaný pravidelne!

    if (millis() - lastUpdate >= 10) {   // ← OPRAVA: 10ms = 100Hz, nie ∞
        lastUpdate = millis();
        tx_msg.seq = ++seqCounter;
        fill_msg(tx_msg, myController);
        Serial2.write((uint8_t*)&tx_msg, sizeof(tx_msg));
        // dump_msg(const ControllerTx_MSG &m);
    }

    // if (millis() - lastPrint >= 500) {
    //     lastPrint = millis();
    //     Serial.printf("seq=%lu connected=%u LX=%d LY=%d\n",
    //         tx_msg.seq, tx_msg.connected,
    //         (int)tx_msg.lStickX, (int)tx_msg.lStickY);
    // }

    vTaskDelay(1);  // watchdog prevencia
}