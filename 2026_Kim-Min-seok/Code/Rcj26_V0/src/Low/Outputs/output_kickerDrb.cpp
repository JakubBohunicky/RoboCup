#include "Low/Outputs/output_kickerDrb.h"
#include "Low/config_hw.h"
#include "driver/gpio.h"
#include <Arduino.h>

static constexpr int KICK_TIME_DELAY = 1000;
static constexpr int KICK_TIME_MS = 100;
static uint32_t lastKickTime = 0;
static bool kicking = false;


void _output_kickerDrb_kick(gpio_num_t pin) {
    if(kicking){
        if(millis() - lastKickTime >= KICK_TIME_MS) {
            gpio_set_level(pin, 0);
            kicking = false;
            lastKickTime = millis();
        }
    } else {
        if(millis() - lastKickTime >= KICK_TIME_DELAY) {
            gpio_set_level(pin, 1);
            kicking = true;
            lastKickTime = millis();
        }    
    }
}

void output_kickerDrb_init_() {
    gpio_set_direction(HW::KickerDrbCfg::DRB_DirPin, GPIO_MODE_OUTPUT);
    gpio_set_level(HW::KickerDrbCfg::DRB_DirPin, OUT::kicker_Drb.drbReverseDir);

    gpio_set_direction(HW::KickerDrbCfg::Kicker_F_Pin, GPIO_MODE_OUTPUT);
    gpio_set_level(HW::KickerDrbCfg::Kicker_F_Pin, OUT::kicker_Drb.kickR);
    gpio_set_direction(HW::KickerDrbCfg::Kicker_R_Pin, GPIO_MODE_OUTPUT);
    gpio_set_level(HW::KickerDrbCfg::Kicker_R_Pin, OUT::kicker_Drb.kickR);

    gpio_set_direction(HW::KickerDrbCfg::DRB_PwmPin, GPIO_MODE_OUTPUT);
    gpio_set_level(HW::KickerDrbCfg::DRB_PwmPin, OUT::kicker_Drb.drbEn);

}


void output_kickerDrb_update() {
    gpio_set_level(HW::KickerDrbCfg::DRB_DirPin, OUT::kicker_Drb.drbReverseDir);
    gpio_set_level(HW::KickerDrbCfg::DRB_PwmPin, OUT::kicker_Drb.drbEn);

    if(OUT::kicker_Drb.kickF || kicking) {
        _output_kickerDrb_kick(HW::KickerDrbCfg::Kicker_F_Pin);
        OUT::kicker_Drb.kickF = false;
    }
    if(OUT::kicker_Drb.kickR || kicking) {
        _output_kickerDrb_kick(HW::KickerDrbCfg::Kicker_R_Pin);
        OUT::kicker_Drb.kickR = false;
    }
}