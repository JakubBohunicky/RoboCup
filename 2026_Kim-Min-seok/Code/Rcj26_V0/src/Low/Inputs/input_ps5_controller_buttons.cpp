#include "Low/Inputs/input_ps5_controller_buttons.h"
#include "Low/config_hw.h"
#include <Arduino.h>


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


static void _input_generic_sw_btn_update(_Raw::HW_BTNs& btn, bool raw) {
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






static void print_controller_rx(const _Raw::ControllerRx_MSG& m) {
    Serial.printf(
        "ver=%u conn=%u seq=%lu up=%lu | dpad[R=%u D=%u U=%u L=%u] | btn[SQ=%u X=%u O=%u TRI=%u] | shoulder[L1=%u R1=%u L3=%u R3=%u] | sys[SH=%u OPT=%u PS=%u TP=%u] | trig[L2P=%u R2P=%u L2=%d R2=%d] | stick[LX=%d LY=%d RX=%d RY=%d]\n",
        m.version,
        m.connected,
        (unsigned long)m.seq,
        (unsigned long)m.uptimeMs,
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


void input_controller_buttons_update() {
    // print_controlleWr_rx(IN::comms.rx_controller_msg);
    
    
}