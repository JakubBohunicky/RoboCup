#include <Arduino.h>
#include <ps5Controller.h>

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
constexpr int UART_BAUD   = 921600;

ControllerTx_MSG tx_msg = {};
uint32_t seqCounter = 0;

static void fill_msg(ControllerTx_MSG& m) {
    m.magicHead  = 0xA55A;
    m.connected  = ps5.isConnected() ? 1 : 0;
    m.right      = ps5.Right();
    m.down       = ps5.Down();
    m.up         = ps5.Up();
    m.left       = ps5.Left();
    m.square     = ps5.Square();
    m.cross      = ps5.Cross();
    m.circle     = ps5.Circle();
    m.triangle   = ps5.Triangle();
    m.l1         = ps5.L1();
    m.r1         = ps5.R1();
    m.l3         = ps5.L3();
    m.r3         = ps5.R3();
    m.share      = ps5.Share();
    m.options    = ps5.Options();
    m.psButton   = ps5.PSButton();
    m.touchpad   = ps5.Touchpad();
    m.l2Pressed  = ps5.L2();
    m.r2Pressed  = ps5.R2();
    m.l2         = ps5.L2Value();
    m.r2         = ps5.R2Value();
    m.lStickX    = ps5.LStickX();
    m.lStickY    = ps5.LStickY();
    m.rStickX    = ps5.RStickX();
    m.rStickY    = ps5.RStickY();   
    m.magicTail  = 0x55AA;
}

void setup() {
    Serial.begin(921600);
    // TX=17, RX=-1 (nepotrebujeme)
    Serial2.begin(UART_BAUD, SERIAL_8N1, -1, UART_TX_PIN);
    //ps5.begin("58:10:31:2f:f7:f0");
    ps5.begin("D3:7F:D4:05:06:07");
    Serial.println("UART sender ready");
}

void loop() {
    static uint32_t lastUpdate = 0;
    static uint32_t lastPrint  = 0;

    if (millis() - lastUpdate >= 10) {
        lastUpdate = millis();
        tx_msg.seq = ++seqCounter;
        fill_msg(tx_msg);
        Serial2.write((uint8_t*)&tx_msg, sizeof(tx_msg));
    }

    if (millis() - lastPrint >= 500) {
        lastPrint = millis();
        Serial.printf("seq=%lu connected=%u LX=%d LY=%d\n",
            tx_msg.seq, tx_msg.connected,
            (int)tx_msg.lStickX, (int)tx_msg.lStickY);
    }
}


