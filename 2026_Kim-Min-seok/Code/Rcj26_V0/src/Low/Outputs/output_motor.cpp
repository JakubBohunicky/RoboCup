#include "Low/Outputs/output_motor.h"
#include "Low/config_hw.h"
#include "driver/gpio.h"
#include <Arduino.h>

void output_motSor_init_() {
    gpio_set_direction(HW::MotorCfg::EnPin, GPIO_MODE_OUTPUT);
    gpio_set_level(HW::MotorCfg::EnPin, OUT::motorAcc.motEn);

    gpio_set_direction(HW::MotorCfg::A_DirPin, GPIO_MODE_OUTPUT);
    gpio_set_direction(HW::MotorCfg::B_DirPin, GPIO_MODE_OUTPUT);
    gpio_set_direction(HW::MotorCfg::C_DirPin, GPIO_MODE_OUTPUT);
    gpio_set_direction(HW::MotorCfg::D_DirPin, GPIO_MODE_OUTPUT);

    
    ledcSetup(0, HW::PWMCfg::PWM_FREQ, HW::PWMCfg::PWM_RES);
}


void output_motor_update() {

}

//po update vystupov treba resetovat akumulator v OUT::
//int out_pwm = 102 + input * (921 - 102);