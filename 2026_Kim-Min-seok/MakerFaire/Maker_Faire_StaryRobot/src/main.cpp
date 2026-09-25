#include <Arduino.h>
#include "motor_angles.h"

#define STOP_MOTORS 0
#define DEBUG_CONTROLLER 0

uint32_t now_ms = 0;

struct SW_BTNs { //button state
    bool LastPos = false;
    bool StablePos = false;
    uint32_t ChangeTime = 0;

    bool Click = false;
    bool LongPress = false;
    bool IsDown = false;
    
    uint32_t PressStartTime = 0;
    bool LongSent = false;
};


struct __attribute__((packed)) ControllerRx_MSG {
    uint16_t magicHead = 0;
    
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

    uint16_t magicTail = 0;
};

struct _Controller_Trigger {
    SW_BTNs pressed;

    int16_t raw = 0;
    float val = 0.0f;

};

struct _Controller_Stick {
    int16_t X = 0;
    int16_t Y = 0;

    float angle = 0.0f;
    float mag = 0.0f;
};

struct Controller {

    uint32_t lastReadTime = 0;

    //inputs
    uint8_t connected = 0;
    uint32_t seq = 0;
    // uint32_t uptimeMs = 0;

    SW_BTNs right;
    SW_BTNs down;
    SW_BTNs up;
    SW_BTNs left;

    SW_BTNs square;
    SW_BTNs cross;
    SW_BTNs circle;
    SW_BTNs triangle;

    SW_BTNs l1;
    SW_BTNs r1;
    SW_BTNs l3;
    SW_BTNs r3;

    SW_BTNs share;
    SW_BTNs options;
    SW_BTNs psButton;
    SW_BTNs touchpad;
    
    _Controller_Trigger l2;
    _Controller_Trigger r2;

    _Controller_Stick lStick;
    _Controller_Stick rStick;
};

struct Comms {
    uint8_t SOCCER_PEER_MAC[6] = {0};
    uint8_t CONTROLLER_PEER_MAC[6] = {0};

    bool initialized = false;
    bool onlineSoccer = false;
    bool onlineController = false;

    // Soccer_MSG rx_soccer_msg = {};
    // Soccer_MSG tx_soccer_msg = {};

    ControllerRx_MSG rx_controller_msg = {};
    // ControllerTx_MSG tx_controller_msg = {};

    volatile bool lastSendOk = false;
    volatile bool sendDone = false;

    volatile bool newSoccerRxPacket = false;
    volatile bool newControllerRxPacket = false;

    uint32_t lastSoccerRxMsg_ms = 0;
    uint32_t lastControllerRxMsg_ms = 0;
    uint32_t lastTxMsg_ms = 0;

    uint32_t txSeq = 0;
};

namespace HW {
  namespace Controller { 
      constexpr uint8_t I2C_ADDR = 0x42;

      constexpr float TRIGG_CONST = 1.0f/255;
      constexpr float DEAD_CONST = 0.1f;
  }
}

Comms comms;
Controller controller;
static void _input_generic_sw_btn_update(SW_BTNs& btn, bool raw) {
    btn.Click = false;
    btn.LongPress = false;

    if (raw != btn.StablePos) {
        if (now_ms - btn.ChangeTime >= 20) {
            btn.StablePos = raw;
            btn.ChangeTime = now_ms;
            if (btn.StablePos == true) {
                btn.PressStartTime = now_ms;
                btn.LongSent = false;
            }
        }
    }

    btn.IsDown = btn.StablePos;
    btn.Click  = (btn.LastPos == true && btn.StablePos == false && btn.LongSent == false);

    if (btn.StablePos == true && btn.LongSent == false) {
        if (now_ms - btn.PressStartTime >= 500) {
            btn.LongPress = true;
            btn.LongSent  = true;
        }
    }

    btn.LastPos = btn.StablePos;
}


static void _debug_print_controller_rx(const ControllerRx_MSG& m) {
    char buf[256];
    snprintf(buf, sizeof(buf),
        "seq=%lu | dpad[R=%u D=%u U=%u L=%u] | btn[SQ=%u X=%u O=%u TRI=%u] | "
        "shoulder[L1=%u R1=%u L3=%u R3=%u] | sys[SH=%u OPT=%u PS=%u TP=%u] | "
        "trig[L2P=%u R2P=%u L2=%d R2=%d] | stick[LX=%d LY=%d RX=%d RY=%d]",
        (unsigned long)m.seq,
        m.right, m.down, m.up, m.left,
        m.square, m.cross, m.circle, m.triangle,
        m.l1, m.r1, m.l3, m.r3,
        m.share, m.options, m.psButton, m.touchpad,
        m.l2Pressed, m.r2Pressed,
        (int)m.l2, (int)m.r2,
        (int)m.lStickX, (int)m.lStickY,
        (int)m.rStickX, (int)m.rStickY
    );
    Serial.println(buf);
}



// ── UART receive buffer ───────────────────────────────────────────
constexpr int UART_RX_PIN = 1;
// constexpr int UART_BAUD   = 115200;
constexpr size_t MSG_SIZE = sizeof(ControllerRx_MSG);

static uint8_t  _uart_buf[MSG_SIZE * 2]; // dvojnásobný buffer pre sync
static uint16_t _uart_buf_pos = 0;
// na začiatku súboru
static uint32_t _lastPacketTime = 0;
constexpr uint32_t CONTROLLER_TIMEOUT_MS = 500; // 500ms bez paketu = offline
// ─────────────────────────────────────────────────────────────────

void input_controller_init_() {
    // RX=1, TX=-1 (nepotrebujeme)
    Serial2.begin(1000000);
    Serial.println("UART receiver ready");
}

void input_controller_update() {

    controller.right.Click    = false;  controller.right.LongPress    = false;
    controller.down.Click     = false;  controller.down.LongPress     = false;
    controller.up.Click       = false;  controller.up.LongPress       = false;
    controller.left.Click     = false;  controller.left.LongPress     = false;
    controller.square.Click   = false;  controller.square.LongPress   = false;
    controller.cross.Click    = false;  controller.cross.LongPress    = false;
    controller.circle.Click   = false;  controller.circle.LongPress   = false;
    controller.triangle.Click = false;  controller.triangle.LongPress = false;
    controller.l1.Click       = false;  controller.l1.LongPress       = false;
    controller.r1.Click       = false;  controller.r1.LongPress       = false;
    controller.l3.Click       = false;  controller.l3.LongPress       = false;
    controller.r3.Click       = false;  controller.r3.LongPress       = false;
    controller.share.Click    = false;  controller.share.LongPress    = false;
    controller.options.Click  = false;  controller.options.LongPress  = false;
    controller.psButton.Click = false;  controller.psButton.LongPress = false;
    controller.touchpad.Click = false;  controller.touchpad.LongPress = false;
    controller.l2.pressed.Click = false; controller.l2.pressed.LongPress = false;
    controller.r2.pressed.Click = false; controller.r2.pressed.LongPress = false;

    // Načítaj všetky dostupné byty
    while (Serial2.available()) {
        if (_uart_buf_pos < sizeof(_uart_buf)) {
            _uart_buf[_uart_buf_pos++] = Serial2.read();
        } else {
            Serial2.read(); // buffer plný — zahoď
        }
    }

    // Spracuj VŠETKY kompletné pakety, použi len POSLEDNÝ
    ControllerRx_MSG latest = {};
    bool gotPacket = false;

    while (_uart_buf_pos >= MSG_SIZE) {
        uint16_t head, tail;
        memcpy(&head, &_uart_buf[0], 2);
        memcpy(&tail, &_uart_buf[MSG_SIZE - 2], 2);

        if (head == 0xA55A && tail == 0x55AA) {
            // Platný — ulož ako latest ale POKRAČUJ ďalej
            memcpy(&latest, _uart_buf, MSG_SIZE);
            gotPacket = true;
            _uart_buf_pos -= MSG_SIZE;
            memmove(_uart_buf, _uart_buf + MSG_SIZE, _uart_buf_pos);
        } else {
            // Neplatný byte — zahoď a hľadaj ďalej
            _uart_buf_pos--;
            memmove(_uart_buf, _uart_buf + 1, _uart_buf_pos);
        }
    }

    if (!gotPacket) {
        // ✅ Nie hneď offline — len ak trvá dlho
        if (now_ms - _lastPacketTime >= CONTROLLER_TIMEOUT_MS) {
            controller.connected = false;
        }
        return;
    }

    // Platný paket prišiel — aktualizuj čas
    _lastPacketTime = now_ms;
    controller.connected = true;
    // ... zvyšok spracovania ostáva rovnaký

    // Teraz spracuj len ten NAJNOVŠÍ paket
    comms.rx_controller_msg = latest;

    #if DEBUG_CONTROLLER
    _debug_print_controller_rx(comms.rx_controller_msg);
    #endif

    controller.connected = true;
    controller.seq = comms.rx_controller_msg.seq;

    _input_generic_sw_btn_update(controller.right,    comms.rx_controller_msg.right);
    _input_generic_sw_btn_update(controller.down,     comms.rx_controller_msg.down);
    _input_generic_sw_btn_update(controller.up,       comms.rx_controller_msg.up);
    _input_generic_sw_btn_update(controller.left,     comms.rx_controller_msg.left);
    _input_generic_sw_btn_update(controller.square,   comms.rx_controller_msg.square);
    _input_generic_sw_btn_update(controller.cross,    comms.rx_controller_msg.cross);
    _input_generic_sw_btn_update(controller.circle,   comms.rx_controller_msg.circle);
    _input_generic_sw_btn_update(controller.triangle, comms.rx_controller_msg.triangle);
    _input_generic_sw_btn_update(controller.l1,       comms.rx_controller_msg.l1);
    _input_generic_sw_btn_update(controller.r1,       comms.rx_controller_msg.r1);
    _input_generic_sw_btn_update(controller.l3,       comms.rx_controller_msg.l3);
    _input_generic_sw_btn_update(controller.r3,       comms.rx_controller_msg.r3);
    _input_generic_sw_btn_update(controller.share,    comms.rx_controller_msg.share);
    _input_generic_sw_btn_update(controller.options,  comms.rx_controller_msg.options);
    _input_generic_sw_btn_update(controller.psButton, comms.rx_controller_msg.psButton);
    _input_generic_sw_btn_update(controller.touchpad, comms.rx_controller_msg.touchpad);
    _input_generic_sw_btn_update(controller.l2.pressed, comms.rx_controller_msg.l2Pressed);
    _input_generic_sw_btn_update(controller.r2.pressed, comms.rx_controller_msg.r2Pressed);

// L2 / R2 triggery — Bluepad32: 0 až 1023, normalizuj na 0.0–1.0
{
    constexpr float TRIGG_NORM = 1.0f / 1023.0f;
    
    float l2Val = (float)comms.rx_controller_msg.l2 * TRIGG_NORM;
    if (l2Val < HW::Controller::DEAD_CONST) l2Val = 0.0f;
    controller.l2.raw = comms.rx_controller_msg.l2;
    controller.l2.val = l2Val;

    float r2Val = (float)comms.rx_controller_msg.r2 * TRIGG_NORM;
    if (r2Val < HW::Controller::DEAD_CONST) r2Val = 0.0f;
    controller.r2.raw = comms.rx_controller_msg.r2;
    controller.r2.val = r2Val;
}

// L stick — Bluepad32: -511 až 512, normalizuj na -1.0 až 1.0
{
    constexpr float STICK_NORM = 1.0f / 512.0f;

    float lx = (float)comms.rx_controller_msg.lStickX * STICK_NORM;
    float ly = (float)comms.rx_controller_msg.lStickY * STICK_NORM;

    // clamp na -1..1 pre istotu
    lx = constrain(lx, -1.0f, 1.0f);
    ly = constrain(ly, -1.0f, 1.0f);

    float lmag = sqrtf(lx*lx + ly*ly);
    if (lmag > 1.0f) lmag = 1.0f;  // kruhový clamp

    if (lmag < HW::Controller::DEAD_CONST) {
        lx = ly = lmag = 0.0f;
    }

    float lang = atan2f(ly, lx) * 180.0f / M_PI + 90.0f;
    if (lang < 0.0f) lang += 360.0f;

    controller.lStick.X     = comms.rx_controller_msg.lStickX;
    controller.lStick.Y     = comms.rx_controller_msg.lStickY;
    controller.lStick.angle = lang;
    controller.lStick.mag   = lmag;
}

// R stick — rovnaká logika
{
    constexpr float STICK_NORM = 1.0f / 512.0f;

    float rx = (float)comms.rx_controller_msg.rStickX * STICK_NORM;
    float ry = (float)comms.rx_controller_msg.rStickY * STICK_NORM;

    rx = constrain(rx, -1.0f, 1.0f);
    ry = constrain(ry, -1.0f, 1.0f);

    float rmag = sqrtf(rx*rx + ry*ry);
    if (rmag > 1.0f) rmag = 1.0f;

    if (rmag < HW::Controller::DEAD_CONST) {
        rx = ry = rmag = 0.0f;
    }

    float rang = atan2f(ry, rx) * 180.0f / M_PI + 90.0f;
    if (rang < 0.0f) rang += 360.0f;

    controller.rStick.X     = comms.rx_controller_msg.rStickX;
    controller.rStick.Y     = comms.rx_controller_msg.rStickY;
    controller.rStick.angle = rang;
    controller.rStick.mag   = rmag;
}
}


#define motorDPWM 3   //PWM pin motor A
#define motorDINB 25  //INA pin motor A
#define motorDINA 27  //INB pin motor A

#define motorAPWM 5   //8; 5   //PWM pin motor B
#define motorAINB 29  //11; 29  //INA pin motor B
#define motorAINA 33  //12; 33  //INB pin motor B

#define motorCPWM 7   //PWM pin motor C
#define motorCINB 37  //INA pin motor C
#define motorCINA 39  //INB pin motor C

#define motorBPWM 9   //PWM pin motor D
#define motorBINB 43  //INA pin motor D
#define motorBINA 45  //INB pin motor D


void motor(byte id, float spd) {

#if !STOP_MOTORS
  switch (id) {
    case 1:
      analogWrite(motorAPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorAINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorAINB, spd > 0 ? LOW : HIGH);
      break;
    case 2:
      analogWrite(motorBPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorBINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorBINB, spd > 0 ? LOW : HIGH);
      break;
    case 3:
      analogWrite(motorCPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorCINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorCINB, spd > 0 ? LOW : HIGH);
      break;
    case 4:
      analogWrite(motorDPWM, spd > 0 ? spd : -spd);
      digitalWrite(motorDINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorDINB, spd > 0 ? LOW : HIGH);
      break;
  }
#else
  switch (id) {
    case 1:
      analogWrite(motorAPWM, spd > 0 ? 0 : 0);
      digitalWrite(motorAINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorAINB, spd > 0 ? LOW : HIGH);
      break;
    case 2:
      analogWrite(motorBPWM, spd > 0 ? 0 : 0);
      digitalWrite(motorBINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorBINB, spd > 0 ? LOW : HIGH);
      break;
    case 3:
      analogWrite(motorCPWM, spd > 0 ? 0 : 0);
      digitalWrite(motorCINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorCINB, spd > 0 ? LOW : HIGH);
      break;
    case 4:
      analogWrite(motorDPWM, spd > 0 ? 0 : 0);
      digitalWrite(motorDINA, spd > 0 ? HIGH : LOW);
      digitalWrite(motorDINB, spd > 0 ? LOW : HIGH);
      break;
  }
#endif
}



#define MA_OFFSET 1
#define MB_OFFSET 1
#define MC_OFFSET 1
#define MD_OFFSET 1

void motion(float speedA, float speedB, float speedC, float speedD) {
  motor(1, speedA * MA_OFFSET);
  motor(2, speedB * MB_OFFSET);
  motor(3, speedC * MC_OFFSET);
  motor(4, speedD * MD_OFFSET);
}

void setup(){
  Serial.begin(1000000);
  input_controller_init_();

    pinMode(motorAPWM, OUTPUT);  //motor A PWM
  pinMode(motorAINA, OUTPUT);  //motor A INA
  pinMode(motorAINB, OUTPUT);  //motor A INB

  pinMode(motorBPWM, OUTPUT);  //motor B PWM
  pinMode(motorBINA, OUTPUT);  //motor B INA
  pinMode(motorBINB, OUTPUT);  //motor B INB

  pinMode(motorCPWM, OUTPUT);  //motor C PWM
  pinMode(motorCINA, OUTPUT);  //motor C INA
  pinMode(motorCINB, OUTPUT);  //motor C INB

  pinMode(motorDPWM, OUTPUT);  //motor D PWM
  pinMode(motorDINA, OUTPUT);  //motor D INA
  pinMode(motorDINB, OUTPUT);  //motor D INB


  pinMode(4, OUTPUT);   // kicker
  pinMode(10, OUTPUT);  // dribbler
}

bool drb = 0;
bool kick = 0;
uint32_t kickTime = 0;
uint32_t lastKick = 0;

void loop(){
    now_ms = millis();
    input_controller_update();

    // pohyb
    uint16_t a = (uint16_t)lround(controller.lStick.angle);
    if (a >= 360) a = 0;  // ← TOTO CHÝBA! Bez toho crash/UB
    float speed = 255.0f * controller.lStick.mag;
    float rNormX = (float)comms.rx_controller_msg.rStickX / 512.0f;
    float outPid = rNormX * 0.23f * 255.0f;

    motion(
        constrain((motionAngles[a][0] * speed) - outPid, -255.0f, 255.0f),
        constrain((motionAngles[a][1] * speed) - outPid, -255.0f, 255.0f),
        constrain((motionAngles[a][2] * speed) - outPid, -255.0f, 255.0f),
        constrain((motionAngles[a][3] * speed) - outPid, -255.0f, 255.0f)
    );

    // KICK
    if (kick) {
        if (now_ms - kickTime >= 100) {
            kick = false;
            analogWrite(4, 0);
            lastKick = now_ms;
        }
    } else if (controller.cross.IsDown && now_ms - lastKick >= 1000) {
        kick = true;
        analogWrite(4, 255);
        kickTime = now_ms;
    }

    // DRIBBLER
    if (controller.circle.Click) {
        drb = !drb;
        analogWrite(10, drb ? 255 : 0);
    }


    // PRIAMY TEST – zahoď po overení
    static bool lastCross = false;
    if (controller.cross.IsDown && !lastCross) {
        Serial.println("KICK TRIGGERED!");
        analogWrite(4, 255);
        delay(100);
        analogWrite(4, 0);
    }
    lastCross = controller.cross.IsDown;
}