#include "Low/I2C_FastADC_init.h"
#include <Wire.h>
#include <FastADC_Mux.h>
#include "Low/config_hw.h"

void I2C_FastADC_init_() {

    Wire.begin(HW::GenericCfg::I2C_SDA_Pin, HW::GenericCfg::I2C_SCL_Pin);
    Wire.setClock(400000); //MAX 800kHz

    fadcInit(8, HW::LineCfg::Line_A_Read_Pin, HW::LineCfg::Line_B_Read_Pin, HW::LineCfg::Line_X_Read_Pin, HW::MotorSenseCfg::A_Spd_Pin, HW::MotorSenseCfg::B_Spd_Pin, HW::MotorSenseCfg::C_Spd_Pin, HW::MotorSenseCfg::D_Spd_Pin, HW::MotorSenseCfg::DRBFR_Spd_Pin);

}