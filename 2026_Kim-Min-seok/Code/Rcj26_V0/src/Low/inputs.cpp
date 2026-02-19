#include "world.h"
#include "Low/inputs.h"
#include "Low/I2C_FastADC_init.h"
#include "Low/Inputs/input_ballIR.h"
#include "Low/Inputs/input_gyro.h"
#include "Low/Inputs/input_line.h"
#include "Low/Inputs/input_motionSense.h"
#include "Low/Inputs/input_pixy.h"

namespace Pheripherials {

    void inputs_init_() {
        I2C_FastADC_init_();
        input_gyro_init_();
        input_line_init_();
        input_motionSense_init_();
        input_pixy_init_();
    }

    void inputs_update() {
        input_ballIR_update();
        input_gyro_update();
        input_line_update();
        input_motionSense_update();
        input_pixy_update();
    }

} // namespace Inputs
