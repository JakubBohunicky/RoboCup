#include "Low/Inputs/input_ballIR.h"
#include "Low/config_hw.h"
#include <Arduino.h>
#include <Wire.h>




void input_ballIR_update() {
    
    Wire.beginTransmission(HW::BallCfg::IR_ADR);
    Wire.write((uint8_t)HW::BallCfg::IR_REG);
    Wire.endTransmission();

    Wire.requestFrom((int)HW::BallCfg::IR_ADR, 4);
    IN::ball.angle = Wire.read() << 8;
    IN::ball.angle |= Wire.read();
    IN::ball.distRaw = Wire.read() << 8;
    IN::ball.distRaw |= Wire.read();

    if (IN::ball.angle >= 360) IN::ball.angle %= 360; //normalize
    IN::ball.angle -= 180;
    

    IN::ball.strength = constrain(((float)IN::ball.distRaw - (float)HW::BallCfg::c_ballEffectiveInputFurthes) / ((float)HW::BallCfg::c_ballEffectiveInputClosest - (float)HW::BallCfg::c_ballEffectiveInputFurthes), 0.0f, 1.0f);
}

