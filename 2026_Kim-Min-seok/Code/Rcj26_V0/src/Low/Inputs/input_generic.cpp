#include "Low/Inputs/input_generic.h"
#include <Wire.h>
#include <FastADC_Mux.h>
#include "Low/config_hw.h"
#include "driver/gpio.h"

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

constexpr int BTN_DEBOUNCE_MS = 20;
constexpr int BTN_LONGPRESS_MS = 500;

BTNs btnSPlus;
BTNs btnSMinus;

void I2C_FastADC_init_() {

    Wire.begin(HW::GenericCfg::I2C_SDA_Pin, HW::GenericCfg::I2C_SCL_Pin);
    Wire.setClock(400000); //MAX 800kHz

    fadcInit(8, HW::LineCfg::Line_A_Read_Pin, HW::LineCfg::Line_B_Read_Pin, HW::LineCfg::Line_X_Read_Pin, HW::MotionSenseCfg::A_Spd_Pin, HW::MotionSenseCfg::B_Spd_Pin, HW::MotionSenseCfg::C_Spd_Pin, HW::MotionSenseCfg::D_Spd_Pin, HW::MotionSenseCfg::DRBFR_Spd_Pin);

}


void input_generic_init_() {
    gpio_set_direction(HW::GenericCfg::BTN_inc_Pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(HW::GenericCfg::BTN_inc_Pin, GPIO_PULLUP_ONLY);
    gpio_set_direction(HW::GenericCfg::BTN_dec_Pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(HW::GenericCfg::BTN_dec_Pin, GPIO_PULLUP_ONLY);

    gpio_set_direction(HW::GenericCfg::BukajModule_Pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(HW::GenericCfg::BukajModule_Pin, GPIO_PULLUP_ONLY);    

    btnSPlus.pin = HW::GenericCfg::BTN_inc_Pin;
    btnSMinus.pin = HW::GenericCfg::BTN_dec_Pin;
}

static void _input_generic_btn_update(BTNs& btn) {
    btn.Click = false;
    btn.LongPress = false;
    uint32_t now = millis();

    bool raw = !gpio_get_level(btn.pin); //active LOW

    if(raw != btn.StablePos) { //edge detection
        if(now - btn.ChangeTime >= BTN_DEBOUNCE_MS) { //debounde
            btn.StablePos = raw;
            btn.ChangeTime = now;
            btn.LongSent = false;

            if(btn.StablePos == true) {
                btn.PressStartTime = now;
            }
        }
    }

    btn.IsDown = btn.StablePos;
    btn.Click = (btn.LastPos == true && btn.StablePos == false);

    if(btn.StablePos == true && btn.LongSent == false) {
        if(now - btn.PressStartTime >= BTN_LONGPRESS_MS) {
            btn.LongPress = true;
            btn.LongSent = true; //dont send again
        }
    }

    btn.LastPos = btn.StablePos;
}

void input_generic_update() {

    IN::generic.bukajModuleEn = gpio_get_level(HW::GenericCfg::BukajModule_Pin);

    _input_generic_btn_update(btnSPlus);
    _input_generic_btn_update(btnSMinus);

    IN::generic.btnPlusClick = btnSPlus.Click;
    IN::generic.btnMinusClick = btnSMinus.Click;

    IN::generic.btnPlusLongPress = btnSPlus.LongPress;
    IN::generic.btnMinusLongPress = btnSMinus.LongPress;

    IN::generic.btnPlusIsDown = btnSPlus.IsDown;
    IN::generic.btnMinusIsDown = btnSMinus.IsDown;
}
