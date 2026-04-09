#include <Arduino.h>
#include "Low/Inputs/input_ps5_controller.h"
#include "Low/config_hw.h"
#include <Arduino.h>
#include <Wire.h>
#include "High/Services/debug.h"

struct BTNs { //button state
    gpio_num_t pin;
    bool LastPos = false;
    bool StablePos = false;
    uint32_t ChangeTime = 0;

    bool Click = false;
    bool LongPress = false;
    bool IsDown = false;
    
    uint32_t PressStartTime = 0;
    bool LongSent = false;
};


static void _input_generic_sw_btn_update(_Raw::SW_BTNs& btn, bool raw) {
    btn.Click = false;
    btn.LongPress = false;

    if(raw != btn.StablePos) { //edge detection
        if(ST::now_ms - btn.ChangeTime >= HW::GenericCfg::SW_BTN_DEBOUNCE_MS) { //debounde
            btn.StablePos = raw;
            btn.ChangeTime = ST::now_ms;
            
            if(btn.StablePos == true) {
              btn.PressStartTime = ST::now_ms;
              btn.LongSent = false;
            }
        }
    }

    btn.IsDown = btn.StablePos;
    btn.Click = (btn.LastPos == true && btn.StablePos == false && btn.LongSent == false);

    if(btn.StablePos == true && btn.LongSent == false) {
        if(ST::now_ms - btn.PressStartTime >= HW::GenericCfg::SW_BTN_LONGPRESS_MS) {
            btn.LongPress = true;
            btn.LongSent = true; //dont send again
        }
    }

    btn.LastPos = btn.StablePos;
}


static void _debug_print_controller_rx(const _Raw::ControllerRx_MSG& m) {
    Serial.printf(
        "seq=%lu | [dpad[R=%u D=%u U=%u L=%u] | btn[SQ=%u X=%u O=%u TRI=%u] | shoulder[L1=%u R1=%u L3=%u R3=%u] | sys[SH=%u OPT=%u PS=%u TP=%u] | trig[L2P=%u R2P=%u L2=%d R2=%d] | stick[LX=%d LY=%d RX=%d RY=%d]\n",
        (unsigned long)m.seq,
        m.right,
        m.down,
        m.up,
        m.left,
        m.square,
        m.cross,
        m.circle,
        m.triangle,
        m.l1,
        m.r1,
        m.l3,
        m.r3,
        m.share,
        m.options,
        m.psButton,
        m.touchpad,
        m.l2Pressed,
        m.r2Pressed,
        (int)m.l2,
        (int)m.r2,
        (int)m.lStickX,
        (int)m.lStickY,
        (int)m.rStickX,
        (int)m.rStickY
    );
}

bool _readControllerMsg(_Raw::ControllerRx_MSG& out) {
    int got = Wire.requestFrom((int)HW::Controller::I2C_ADDR, (int)sizeof(_Raw::ControllerRx_MSG), true);
    if (got != sizeof(_Raw::ControllerRx_MSG)) {
        while (Wire.available()) Wire.read();
        return false;
    }

    uint8_t* p = (uint8_t*)&out;
    for (size_t i = 0; i < sizeof(_Raw::ControllerRx_MSG); i++) {
        if (!Wire.available()) return false;
        p[i] = Wire.read();
    }
    return true;
}



void input_controller_update() {
    
    if (!_readControllerMsg(IN::comms.rx_controller_msg)) {
        Serial.println("I2C read failed");
        return;
    }

    #ifdef DEBUG_CONTROLLER
        _debug_print_controller_rx(IN::comms.rx_controller_msg);
    #endif

    IN::controller.connected = IN::comms.rx_controller_msg.connected;
    IN::controller.seq = IN::comms.rx_controller_msg.seq;

    _input_generic_sw_btn_update(IN::controller.right, IN::comms.rx_controller_msg.right);
    _input_generic_sw_btn_update(IN::controller.down, IN::comms.rx_controller_msg.down);
    _input_generic_sw_btn_update(IN::controller.up, IN::comms.rx_controller_msg.up);
    _input_generic_sw_btn_update(IN::controller.left, IN::comms.rx_controller_msg.left);

    _input_generic_sw_btn_update(IN::controller.square, IN::comms.rx_controller_msg.square);
    _input_generic_sw_btn_update(IN::controller.cross, IN::comms.rx_controller_msg.cross);
    _input_generic_sw_btn_update(IN::controller.circle, IN::comms.rx_controller_msg.circle);
    _input_generic_sw_btn_update(IN::controller.triangle, IN::comms.rx_controller_msg.triangle);

    _input_generic_sw_btn_update(IN::controller.l1, IN::comms.rx_controller_msg.l1);
    _input_generic_sw_btn_update(IN::controller.r1, IN::comms.rx_controller_msg.r1);
    _input_generic_sw_btn_update(IN::controller.l3, IN::comms.rx_controller_msg.l3);
    _input_generic_sw_btn_update(IN::controller.r3, IN::comms.rx_controller_msg.r3);

    _input_generic_sw_btn_update(IN::controller.share, IN::comms.rx_controller_msg.share);
    _input_generic_sw_btn_update(IN::controller.options, IN::comms.rx_controller_msg.options);
    _input_generic_sw_btn_update(IN::controller.psButton, IN::comms.rx_controller_msg.psButton);
    _input_generic_sw_btn_update(IN::controller.touchpad, IN::comms.rx_controller_msg.touchpad);

    _input_generic_sw_btn_update(IN::controller.l2.pressed, IN::comms.rx_controller_msg.l2Pressed);
    _input_generic_sw_btn_update(IN::controller.r2.pressed, IN::comms.rx_controller_msg.r2Pressed);


    float l2Val = (float)IN::comms.rx_controller_msg.l2 * HW::Controller::TRIGG_CONST;
    if(l2Val < HW::Controller::DEAD_CONST) {
        l2Val = 0.0f;
    }
    IN::controller.l2.raw = IN::comms.rx_controller_msg.l2;
    IN::controller.l2.val = l2Val;

    float r2Val = (float)IN::comms.rx_controller_msg.r2 * HW::Controller::TRIGG_CONST;
    if(r2Val < HW::Controller::DEAD_CONST) {
        r2Val = 0.0f;
    }
    IN::controller.r2.raw = IN::comms.rx_controller_msg.r2;
    IN::controller.r2.val = r2Val;


    IN::controller.lStick.X = IN::comms.rx_controller_msg.lStickX;
    IN::controller.lStick.Y = IN::comms.rx_controller_msg.lStickY;

    float lx = (float)IN::comms.rx_controller_msg.lStickX * HW::Controller::TRIGG_CONST;
    float ly = (float)IN::comms.rx_controller_msg.lStickY * HW::Controller::TRIGG_CONST;
    float lmag = sqrtf(lx*lx + ly*ly);
    if (lmag < HW::Controller::DEAD_CONST) {
        lx = 0.0f;
        ly = 0.0f;
        lmag = 0.0f;
    }
    float lang = atan2f(ly, lx) * 180.0f / M_PI - 90;
    if(lang < 0) {
        lang += 360.0f;
    }
    
    IN::controller.lStick.angle = lang;
    IN::controller.lStick.mag = lmag;


    IN::controller.rStick.X = IN::comms.rx_controller_msg.rStickX;
    IN::controller.rStick.Y = IN::comms.rx_controller_msg.rStickY;

    float rx = (float)IN::comms.rx_controller_msg.rStickX * HW::Controller::TRIGG_CONST;
    float ry = (float)IN::comms.rx_controller_msg.rStickY * HW::Controller::TRIGG_CONST;
    float rmag = sqrtf(rx*rx + ry*ry);
    if (rmag < HW::Controller::DEAD_CONST) {
        rx = 0.0f;
        ry = 0.0f;
        rmag = 0.0f;
    }
    float rang = atan2f(ry, rx) * 180.0f / M_PI - 90;
    if(rang < 0) {
        rang += 360.0f;
    }
    
    IN::controller.rStick.angle = rang;
    IN::controller.rStick.mag = rmag;


    // Serial.printf("ang: %0.2f, mag: %0.2f || ang: %0.2f, mag: %0.2f ||  l2: %0.2f, r2: %0.2f\n", IN::controller.lStick.angle, IN::controller.lStick.mag, IN::controller.rStick.angle, IN::controller.rStick.mag, IN::controller.l2.val, IN::controller.r2.val);
}