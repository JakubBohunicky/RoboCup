#include "Low/Outputs/output_kickerDrb.h"
#include "Low/config_hw.h"
#include "driver/gpio.h"


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
    
}