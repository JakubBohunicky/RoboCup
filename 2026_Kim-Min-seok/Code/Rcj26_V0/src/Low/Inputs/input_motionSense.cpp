#include "Low/Inputs/input_motionSense.h"
#include "driver/gpio.h"
#include "Low/config_hw.h"
#include <FastADC_Mux.h>

static uint16_t speeds_ADC[5];

static constexpr uint8_t motion_CH_A = 3;
static constexpr uint8_t motion_CH_B = 4;
static constexpr uint8_t motion_CH_C = 5;
static constexpr uint8_t motion_CH_D = 6;
static constexpr uint8_t motion_CH_DRBFR = 7;

static constexpr uint8_t motion_motFR = 0;
static constexpr uint8_t motion_motFL = 1;
static constexpr uint8_t motion_motRL = 2;
static constexpr uint8_t motion_motRR = 3;
static constexpr uint8_t motion_motDRBRF = 4;

static constexpr float motion_ADC_Const = 1.0f/HW::MotionSenseCfg::ADC_maxVal;

void _input_motionSense_readSpeed() {
    speeds_ADC[motion_motFR] = analogReadFast(motion_CH_A);
    speeds_ADC[motion_motFL] = analogReadFast(motion_CH_B);
    speeds_ADC[motion_motRL] = analogReadFast(motion_CH_C);
    speeds_ADC[motion_motRR] = analogReadFast(motion_CH_D);
    speeds_ADC[motion_motDRBRF] = analogReadFast(motion_CH_DRBFR);
}



void input_motionSense_init_() {
    gpio_set_direction(HW::MotionSenseCfg::DRB_SW_F_Pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(HW::MotionSenseCfg::DRB_SW_F_Pin, GPIO_PULLUP_ONLY);
    gpio_set_direction(HW::MotionSenseCfg::DRB_SW_R_Pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(HW::MotionSenseCfg::DRB_SW_R_Pin, GPIO_PULLUP_ONLY);


    speeds_ADC[motion_motDRBRF] = analogReadFast(motion_CH_DRBFR);

    if(speeds_ADC[motion_motDRBRF] > (HW::MotionSenseCfg::ADC_maxVal/2)) {
        ST::state.isRobot_A = false;
    }

    //fastADC init is in own cpp file
}


void input_motionSense_update() {
    _input_motionSense_readSpeed();

    IN::motionSens.motSpeed = 0.25f * (
        (float)speeds_ADC[motion_motFR] * motion_ADC_Const +
        (float)speeds_ADC[motion_motFL] * motion_ADC_Const +
        (float)speeds_ADC[motion_motRL] * motion_ADC_Const +
        (float)speeds_ADC[motion_motRR] * motion_ADC_Const );

    // if(ST::state.isRobot_A == true) { //ROBOT_A
    //     IN::motionSens.drbSpeed = speeds_ADC[motion_motDRBRF] * motion_ADC_Const;
    // } else { //ROBOT_B
    //     IN::motionSens.drbSpeed = 1.0f - (speeds_ADC[motion_motDRBRF] * motion_ADC_Const);
    // }
    IN::motionSens.drbF = !gpio_get_level(HW::MotionSenseCfg::DRB_SW_F_Pin);
    IN::motionSens.drbR = !gpio_get_level(HW::MotionSenseCfg::DRB_SW_R_Pin);
}