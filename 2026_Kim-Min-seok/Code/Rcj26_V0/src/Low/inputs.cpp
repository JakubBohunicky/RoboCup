#include "world.h"
#include "Low/inputs.h"
#include "Low/Inputs/input_generic.h"
#include "Low/Inputs/input_ballIR.h"
#include "Low/Inputs/input_gyro.h"
#include "Low/Inputs/input_line.h"
#include "Low/Inputs/input_motionSense.h"
#include "Low/Inputs/input_pixy.h"
#include <Arduino.h>

static uint32_t times[] = {0, 0, 0, 0, 0};



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
        // input_gyro_init_();
        input_line_init_();
        input_motionSense_init_();
        // input_pixy_init_();
    }

    void inputs_update() {
        uint32_t now = millis();

        if(now - times[0] >= 1) { //1kHz
            // input_gyro_update();
            times[0] = now;
        }
        if(now - times[1] >= 3) { //333Hz
            input_line_update();
            input_motionSense_update();
            times[1] = now;
        }
        if(now - times[2] >= 5) { //200Hz
            // input_ballIR_update();
            times[2] = now;
        }
        if(now - times[3] >= 33) { //30Hz
            // input_pixy_update();
            input_generic_update();
            times[3] = now;
        }
    }
}
