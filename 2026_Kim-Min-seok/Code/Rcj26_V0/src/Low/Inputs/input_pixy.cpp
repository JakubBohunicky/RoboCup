#include "Low/Inputs/input_pixy.h"
#include <Arduino.h>
#include <Pixy2I2C.h>
#include "Low/config_hw.h"
#include "High/Services/debug.h"

static Pixy2I2C pixy;

#if DEBUG_LED_GOAL
static uint8_t debug_goal_prev_state = 255;
#endif

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
        // return;
    }

    for(int i = 0; i < n; i++) {
        auto &b = pixy.ccc.blocks[i];

        //!!!! pixyyy - spravit to tak ze prva polovica blokov bude zlta branka a druha polovica modra branka a nech si vyberie ze kde streli ale primarne cela branka cize asi prva nech tym preloopuje

        IN::goalEnemy.close = false;
        IN::goalOur.close = false;

        if(b.m_y >= HW::PixyCfg::c_pixy_objMinHeight) {
            if(b.m_signature == (uint16_t)ST::soccer.enemyGoal) { //if blue SIG == 1
                IN::goalEnemy.seen = true;
                IN::goalEnemy.angle = _input_pixy_xToAngle(b.m_x);
                // IN::goalEnemy.size = b.m_width * b.m_height;
                if(b.m_height >= 50) {
                    IN::goalEnemy.close = true;
                }
                #if DEBUG_PIXY 
                    Serial.print(b.m_height);
                    Serial.print("  ");
                #endif

            } else if(b.m_signature != (uint16_t)ST::soccer.enemyGoal) { //if yellow SIG == 0
                IN::goalOur.seen = true;
                IN::goalOur.angle = _input_pixy_xToAngle(b.m_x);
                // IN::goalOur.size = b.m_width * b.m_height;
                if(b.m_height >= 60) {
                    IN::goalOur.close = true;
                }
            }

            // Serial.print(b.m_width);
            // Serial.print("  ;   ");
            // Serial.print(b.m_height);
            // Serial.print("  ;   ||");
        }
    }

    #if DEBUG_PIXY 
        Serial.print(IN::goalEnemy.seen);
        Serial.print("  ");
        Serial.print(IN::goalEnemy.close);
        Serial.print("  ");
        Serial.print(IN::goalEnemy.angle);
        Serial.print("  ||  ");

        Serial.print(IN::goalOur.seen);
        Serial.print("  ");
        Serial.print(IN::goalOur.close);
        Serial.print("  ");
        Serial.print(IN::goalOur.angle);
        Serial.println("");

        #endif


#if DEBUG_LED_GOAL
    uint8_t debug_goal_now_state = 0;

    if (IN::goalEnemy.seen) {
        debug_goal_now_state = 1;   // enemy
    }
    else if (IN::goalOur.seen) {
        debug_goal_now_state = 2;   // our
    }
    else {
        debug_goal_now_state = 0;   // off
    }

    if (debug_goal_now_state != debug_goal_prev_state) {
        debug_goal_prev_state = debug_goal_now_state;
        OUT::led_Debug.needsUpdate = true;

        if (debug_goal_now_state == 1) {
            if (ST::soccer.enemyGoal == ST::Types::goal_t::Yellow) {
                OUT::led_Debug.color[1] = CRGB::Yellow;
            } else {
                OUT::led_Debug.color[1] = CRGB::Blue;
            }
            // Serial.println("goal state -> ENEMY");
        }
        else if (debug_goal_now_state == 2) {
            if (ST::soccer.enemyGoal == ST::Types::goal_t::Yellow) {
                OUT::led_Debug.color[1] = CRGB::Blue;
            } else {
                OUT::led_Debug.color[1] = CRGB::Yellow;
            }
            // Serial.println("goal state -> OUR");
        }
        else {
            OUT::led_Debug.color[1] = CRGB::Black;
            // Serial.println("goal state -> OFF");
        }
    }
#endif

}