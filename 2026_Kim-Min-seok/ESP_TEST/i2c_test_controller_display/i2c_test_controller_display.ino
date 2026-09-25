#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

constexpr int SDA_PIN = 8;
constexpr int SCL_PIN = 9;
constexpr uint32_t I2C_FREQ = 400000UL;

constexpr uint8_t OLED_ADDR = 0x3C;
constexpr uint8_t SLAVE_ADDR = 0x42;

constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;

// true = bude refreshovat OLED
// false = OLED sa iba inicializuje, ale nebude posielat pravidelny display.display()
bool testDisplayTraffic = false;

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1,
    400000UL,
    400000UL
);

struct __attribute__((packed)) ControllerPacket {
    uint8_t connected;
    uint32_t seq;

    uint8_t right;
    uint8_t down;
    uint8_t up;
    uint8_t left;

    uint8_t square;
    uint8_t cross;
    uint8_t circle;
    uint8_t triangle;

    uint8_t l1;
    uint8_t r1;
    uint8_t l3;
    uint8_t r3;

    uint8_t share;
    uint8_t options;
    uint8_t psButton;
    uint8_t touchpad;

    uint8_t l2Pressed;
    uint8_t r2Pressed;

    int16_t l2;
    int16_t r2;
    int16_t lStickX;
    int16_t lStickY;
    int16_t rStickX;
    int16_t rStickY;
};

static void scanI2C() {
    Serial.println("Scanning...");
    for (uint8_t addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        uint8_t err = Wire.endTransmission();
        if (err == 0) {
            Serial.printf("I2C device found at address 0x%02X\n", addr);
        }
    }
    Serial.println("done\n");
}

static bool readSlavePacket(ControllerPacket& pkt, int& gotBytes) {
    gotBytes = Wire.    ((int)SLAVE_ADDR, (int)sizeof(ControllerPacket), true);

    if (gotBytes != (int)sizeof(ControllerPacket)) {
        while (Wire.available()) {
            Wire.read();
        }
        return false;
    }

    uint8_t* p = reinterpret_cast<uint8_t*>(&pkt);
    for (size_t i = 0; i < sizeof(ControllerPacket); i++) {
        if (!Wire.available()) {
            return false;
        }
        p[i] = Wire.read();
    }

    return true;
}

static void initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR, true, false)) {
        Serial.println("SSD1306 begin failed");
        return;
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("OLED init OK");
    display.display();
}

static void updateDisplay(
    uint32_t okCount,
    uint32_t failCount,
    uint32_t staleCount,
    uint32_t shortReadCount,
    const ControllerPacket& pkt
) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.printf("OK: %lu\n", (unsigned long)okCount);
    display.printf("FAIL: %lu\n", (unsigned long)failCount);
    display.printf("STL: %lu\n", (unsigned long)staleCount);
    display.printf("SHR: %lu\n", (unsigned long)shortReadCount);
    display.printf("SEQ: %lu\n", (unsigned long)pkt.seq);
    display.printf("C:%u LX:%d\n", pkt.connected, (int)pkt.lStickX);
    display.printf("LY:%d RX:%d\n", (int)pkt.lStickY, (int)pkt.rStickX);
    display.printf("RY:%d\n", (int)pkt.rStickY);
    display.display();
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n=== I2C DISPLAY vs SLAVE TEST ===");

    Wire.setBufferSize(128);
    Wire.begin(SDA_PIN, SCL_PIN);
    Wire.setClock(I2C_FREQ);

    scanI2C();
    initDisplay();

    Serial.printf("I2C freq: %lu\n", (unsigned long)I2C_FREQ);
    Serial.printf("OLED traffic test: %s\n", testDisplayTraffic ? "ON" : "OFF");
    Serial.println("Watch ok/fail/stale/short and seq progression.\n");
}

void loop() {
    static uint32_t okCount = 0;
    static uint32_t failCount = 0;
    static uint32_t staleCount = 0;
    static uint32_t shortReadCount = 0;
    static uint32_t lastPrint = 0;
    static uint32_t lastDisplay = 0;
    static uint32_t lastSeq = 0;
    static ControllerPacket pkt = {};
    static ControllerPacket lastGoodPkt = {};

    int gotBytes = 0;
    bool ok = readSlavePacket(pkt, gotBytes);

    if (ok) {
        okCount++;

        if (pkt.seq == lastSeq) {
            staleCount++;
        } else {
            lastSeq = pkt.seq;
        }

        lastGoodPkt = pkt;
    } else {
        failCount++;
        if (gotBytes > 0 && gotBytes < (int)sizeof(ControllerPacket)) {
            shortReadCount++;
        }
        Serial.printf("I2C read failed from 0x42, got=%d expected=%u\n",
                      gotBytes,
                      (unsigned)sizeof(ControllerPacket));
    }

    if (millis() - lastPrint >= 500) {
        lastPrint = millis();
        Serial.printf(
            "ok=%lu fail=%lu stale=%lu short=%lu seq=%lu conn=%u LX=%d LY=%d RX=%d RY=%d\n",
            (unsigned long)okCount,
            (unsigned long)failCount,
            (unsigned long)staleCount,
            (unsigned long)shortReadCount,
            (unsigned long)lastGoodPkt.seq,
            lastGoodPkt.connected,
            (int)lastGoodPkt.lStickX,
            (int)lastGoodPkt.lStickY,
            (int)lastGoodPkt.rStickX,
            (int)lastGoodPkt.rStickY
        );
    }

    if (testDisplayTraffic && millis() - lastDisplay >= 100) {
        lastDisplay = millis();
        updateDisplay(okCount, failCount, staleCount, shortReadCount, lastGoodPkt);
    }

    delay(10);
}