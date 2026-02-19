#include "Low/Inputs/input_generic.h"
#include <Wire.h>
#include <FastADC_Mux.h>
#include "Low/config_hw.h"
#include "driver/gpio.h"

struct BTNs { //button state
    gpio_num_t pin;
    bool btnLastPos = false;
    bool btnStablePos = false;
    uint32_t btnChangeTime = 0;
    bool btnActive = false;
};

constexpr int BTN_DEBOUNCE_MS = 20;

BTNs btnS_dec;
BTNs btnS_inc;

void I2C_FastADC_init_() {

    Wire.begin(HW::GenericCfg::I2C_SDA_Pin, HW::GenericCfg::I2C_SCL_Pin);
    Wire.setClock(400000); //MAX 800kHz

    fadcInit(8, HW::LineCfg::Line_A_Read_Pin, HW::LineCfg::Line_B_Read_Pin, HW::LineCfg::Line_X_Read_Pin, HW::MotorSenseCfg::A_Spd_Pin, HW::MotorSenseCfg::B_Spd_Pin, HW::MotorSenseCfg::C_Spd_Pin, HW::MotorSenseCfg::D_Spd_Pin, HW::MotorSenseCfg::DRBFR_Spd_Pin);

}


void input_generic_init_() {
    gpio_set_direction(HW::GenericCfg::BTN_inc_Pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(HW::GenericCfg::BTN_inc_Pin, GPIO_PULLUP_ONLY);
    gpio_set_direction(HW::GenericCfg::BTN_dec_Pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(HW::GenericCfg::BTN_dec_Pin, GPIO_PULLUP_ONLY);

    gpio_set_direction(HW::GenericCfg::BukajModule_Pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(HW::GenericCfg::BukajModule_Pin, GPIO_PULLUP_ONLY);    

    btnS_dec.pin = HW::GenericCfg::BTN_dec_Pin;
    btnS_inc.pin = HW::GenericCfg::BTN_inc_Pin;
}

static void _input_generic_btn_update(BTNs& btn) {
    bool raw = !gpio_get_level(btn.pin);

    if(raw != btn.btnStablePos) { //edge detection

        if(millis() - btn.btnChangeTime >= BTN_DEBOUNCE_MS) {
            btn.btnStablePos = raw;
            btn.btnChangeTime = millis();
        }
    } else { //no change
        btn.btnChangeTime = millis();
    }

    btn.btnActive = (btn.btnLastPos == true && btn.btnStablePos == false);
    btn.btnLastPos = btn.btnStablePos;
}


void input_generic_update() {

    IN::generic.bukajModuleEn = gpio_get_level(HW::GenericCfg::BukajModule_Pin);

    _input_generic_btn_update(btnS_inc);
    _input_generic_btn_update(btnS_dec);

    IN::generic.btn_incA = btnS_inc.btnActive;
    IN::generic.btn_decA = btnS_dec.btnActive;
}
