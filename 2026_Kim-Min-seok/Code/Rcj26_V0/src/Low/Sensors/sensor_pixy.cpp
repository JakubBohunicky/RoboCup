#include "Low/Sensors/sensor_pixy.h"
#include <Arduino.h>
#include <Pixy2I2C.h>
#include "Low/config_hw.h"

static Pixy2I2C pixy;


void sensor_pixy_init_()
{
    int8_t r = pixy.init();          // default adresa je 0x54
    Serial.println(r == 0 ? "Pixy init OK" : "Pixy init FAIL");
}

float sensor_pixy_xToAngle(int x){

    float cx = HW::PixyCfg::c_pixy_frameWidth * 0.5f;
    float nx = (x - cx) / cx;
    return nx * (HW::PixyCfg::c_pixy_FOV * 0.5f);

}

void sensor_pixy_update(WorldIn& in) { //Angle from -180 to 180
    in.goalEnemy = {};
    in.goalOur = {};

    int8_t n = pixy.ccc.getBlocks();
    if(n <= 0) return;

    for(int i = 0; i < n; i++) {
        auto &b = pixy.ccc.blocks[i];

        if(b.m_y >= HW::PixyCfg::c_pixy_objMinHeight) {
            if(b.m_signature == HW::PixyCfg::c_GoalSigEnemy) {
                in.goalEnemy.seen = true;
                in.goalEnemy.angle = sensor_pixy_xToAngle(b.m_x);
                in.goalEnemy.size = b.m_width * b.m_height;

            } else if(b.m_signature == HW::PixyCfg::c_GoalSigOur) {
                in.goalOur.seen = true;
                in.goalOur.angle = sensor_pixy_xToAngle(b.m_x);
                in.goalOur.size = b.m_width * b.m_height;
            }
        }
    }
}


