#include "Low/Inputs/input_ballIR.h"
#include "Low/config_hw.h"
#include "Low/inputs.h"
#include <Arduino.h>
#include <Wire.h>



static uint16_t ballAngleRaw = 0;

void input_ballIR_update() {    
    Wire.beginTransmission(HW::BallCfg::IR_ADR);
    Wire.write((uint8_t)HW::BallCfg::IR_REG);
    Wire.endTransmission();

    Wire.requestFrom((int)HW::BallCfg::IR_ADR, 4);
    ballAngleRaw = Wire.read() << 8;
    ballAngleRaw |= Wire.read();
    IN::ball.distRaw = Wire.read() << 8;
    IN::ball.distRaw |= Wire.read();

    if(IN::ball.distRaw >= HW::BallCfg::c_ballignoreDistance) {
        IN::ball.angle = input_wrap180(IN::line.angle);
        IN::ball.angle_ToNField = input_wrap180(IN::line.angle - IN::gyro.offset_ToNField);
    }
    IN::ball.strength = constrain(((float)IN::ball.distRaw - (float)HW::BallCfg::c_ballEffectiveInputFurthes) / ((float)HW::BallCfg::c_ballEffectiveInputClosest - (float)HW::BallCfg::c_ballEffectiveInputFurthes), 0.0f, 1.0f);
}

