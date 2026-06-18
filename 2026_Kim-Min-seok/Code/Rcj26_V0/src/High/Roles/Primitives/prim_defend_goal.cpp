#include "High/Roles/Primitives/prim_defend_goal.h"
#include "High/Services/motion.h"
#include "Arduino.h"

// static bool behindLine = false;
int8_t outSideOfBounds = 0;  // -1 to 1; 0 mems all good :)



namespace Prim {

    void defend_goal() {
        
        // Motion::rotate_ToNField(0.0f);
        float rotAng = constrain(IN::ball.angle, -45.0f, 45.0f);
        Motion::rotate_ToNField(rotAng, ST::pid.slowPIDCfg);
        Motion::addMotion_ToNField(0.0f, 0.5f * IN::line.depth_Y);


        float movStrenght = sin(DEG_TO_RAD * IN::ball.angle);
        movStrenght = constrain(movStrenght * 100 * IN::ball.proximity, -0.4f, 0.4f);
        Motion::addMotion_ToNField(90.0f, movStrenght);


        Serial.print(IN::line.defender_outOfBounds);
        Serial.print("  ");
        Serial.println(IN::line.defender_crossedSide);


    }


}