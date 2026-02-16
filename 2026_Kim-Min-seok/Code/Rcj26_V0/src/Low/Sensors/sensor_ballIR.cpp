#include "Low/Sensors/sensor_ballIR.h"
#include "Low/config_hw.h"
#include <Arduino.h>
#include <Wire.h>




void sensor_ballIR_update(WorldIn& in) {
    
    Wire.beginTransmission(HW::BallCfg::IR_ADR);
    Wire.write((uint8_t)HW::BallCfg::IR_REG);
    Wire.endTransmission();

    Wire.requestFrom((int)HW::BallCfg::IR_ADR, 4);
    in.ball.angle = Wire.read() << 8;
    in.ball.angle |= Wire.read();
    in.ball.distRaw = Wire.read() << 8;
    in.ball.distRaw |= Wire.read();

    if (in.ball.angle >= 360) in.ball.angle %= 360;
    in.ball.angle -= 180;

    in.ball.strenght = constrain(((float)in.ball.distRaw - (float)HW::BallCfg::c_ballEffectiveInputFurthes) / ((float)HW::BallCfg::c_ballEffectiveInputClosest - (float)HW::BallCfg::c_ballEffectiveInputFurthes), 0.0f, 1.0f);
}

