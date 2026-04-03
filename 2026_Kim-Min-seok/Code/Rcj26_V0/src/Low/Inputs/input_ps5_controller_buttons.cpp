#include "Low/Inputs/input_ps5_controller_buttons.h"
#include "Low/config_hw.h"


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


void input_controller_buttons_update() {
    
}