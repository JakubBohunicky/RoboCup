#include "Low/Inputs/input_pixy.h"
#include <Arduino.h>
#include <Pixy2I2C.h>
#include "Low/config_hw.h"
#include "High/Services/debug.h"

static Pixy2I2C pixy;


void input_pixy_init_()
{
    int8_t r = pixy.init();          // default adresa je 0x54
    Serial.println(r == 0 ? "Pixy init OK" : "Pixy init FAIL");
}

float _input_pixy_xToAngle(int x){

    float cx = HW::PixyCfg::c_pixy_frameWidth * 0.5f;
    float nx = (x - cx) / cx;
    return nx * (HW::PixyCfg::c_pixy_FOV * 0.5f);

}

void input_pixy_update() { //Angle from -180 to 180
    IN::goalEnemy = {};
    IN::goalOur = {};

    int8_t n = pixy.ccc.getBlocks();
    if(n <= 0) {
        #if DEBUG_PIXY
            Serial.println("---------------------");
        #endif
        return;
    }

    for(int i = 0; i < n; i++) {
        auto &b = pixy.ccc.blocks[i];

        //!!!! pixyyy - spravit to tak ze prva polovica blokov bude zlta branka a druha polovica modra branka a nech si vyberie ze kde streli ale primarne cela branka cize asi prva nech tym preloopuje

        // if(b.m_y >= HW::PixyCfg::c_pixy_objMinHeight) {
            if(b.m_signature == (uint16_t)ST::soccer.enemyGoal) { //if blue SIG == 1
                IN::goalEnemy.seen = true;
                IN::goalEnemy.angle = _input_pixy_xToAngle(b.m_x);
                IN::goalEnemy.size = b.m_width * b.m_height;

            } else if(b.m_signature != (uint16_t)ST::soccer.enemyGoal) { //if yellow SIG == 0
                IN::goalOur.seen = true;
                IN::goalOur.angle = _input_pixy_xToAngle(b.m_x);
                IN::goalOur.size = b.m_width * b.m_height;
            }
        // }
    }

    #if DEBUG_PIXY 
        Serial.print(IN::goalEnemy.seen);
        Serial.print("  ");
        Serial.print(IN::goalEnemy.angle);
        Serial.print("  ||  ");

        Serial.print(IN::goalOur.seen);
        Serial.print("  ");
        Serial.print(IN::goalOur.angle);
        Serial.println("");

        #endif
}