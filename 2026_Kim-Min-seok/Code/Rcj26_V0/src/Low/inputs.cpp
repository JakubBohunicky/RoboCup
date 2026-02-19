#include "world.h"
#include "Low/inputs.h"
#include "Low/Inputs/input_generic.h"
#include "Low/Inputs/input_ballIR.h"
#include "Low/Inputs/input_gyro.h"
#include "Low/Inputs/input_line.h"
#include "Low/Inputs/input_motionSense.h"
#include "Low/Inputs/input_pixy.h"



int16_t input_wrap180(int16_t a) { //normalize from -180 to 180
    a %= 360; 
    if(a<0) a+=360;
    if(a>180) a-=360;
    return a;
}



namespace Pheripherials {

    void inputs_init_() {
        I2C_FastADC_init_();
        input_generic_init_();
        input_gyro_init_();
        input_line_init_();
        input_motionSense_init_();
        input_pixy_init_();
    }

    void inputs_update() {
        input_gyro_update();
        input_line_update();
        input_ballIR_update();
        input_pixy_update();
        input_motionSense_update();
        input_generic_update();
    }

}
