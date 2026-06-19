#include "High/Roles/Primitives/prim_defend_goal.h"
#include "High/Services/motion.h"
#include "Arduino.h"

// static bool behindLine = false;
int8_t outSideOfBounds = 0;  // -1 to 1; 0 mems all good :)



namespace Prim {

    void defend_goal() {
        
        Motion::rotate_ToNField(0.0f);
        // float rotAng = constrain(IN::ball.angle, -45.0f, 45.0f);
        // Motion::rotate_ToNField(rotAng, ST::pid.slowPIDCfg);
        Motion::addMotion_ToNField(0.0f, 0.3f * IN::line.depth_Y);


        if(IN::line.defender_outOfBounds) {
            if(IN::line.defender_crossedSide == 1) {
                Motion::addMotion_ToNField(-90.0f, 0.4f);
            } else if (IN::line.defender_crossedSide == -1) {
                Motion::addMotion_ToNField(90.0f, 0.4f);
            }
        } else {
            float movStrenght = sin(DEG_TO_RAD * IN::ball.angle);
            movStrenght = constrain(movStrenght * 10 * IN::ball.proximity, -0.3f, 0.3f);
            Motion::addMotion_ToNField(90.0f, movStrenght);
        }


        // Serial.print(IN::line.defender_outOfBounds);
        // Serial.print("  ");
        // Serial.println(IN::line.defender_crossedSide);


    }


}