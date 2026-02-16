#include "Low/I2C.h"
#include <Wire.h>
#include "Low/config_hw.h"

void I2C_init_() {

    Wire.begin(HW::GENERIC::I2C_SDA_Pin, HW::GENERIC::I2C_SCL_Pin);
    Wire.setClock(400000); //MAX 800kHz

}