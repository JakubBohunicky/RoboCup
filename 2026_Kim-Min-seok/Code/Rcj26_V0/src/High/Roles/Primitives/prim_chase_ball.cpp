#include "High/Roles/Primitives/prim_chase_ball.h"
#include "High/Services/motion.h"
#include "Low/inputs.h"
#include "High/Services/debug.h"

namespace CFG {

    // static constexpr float 

    // static constexpr float maxBehindOffset = 70.0f;
    static constexpr float orbitScale = 0.95f;
    static constexpr float closeProximity = 0.8f;
}


float closeOrbitAngle(float ballAngle, float proximity) {
    float s = (ballAngle >= 0.0f) ? 1.0f : -1.0f;
    float a = fabs(ballAngle);
    float out = 0.0f;

    // if (a < 11.0f) {
    //     out = 3.0f * a * CFG::orbitScale;
    // } else if (a < 21.0f) {
    //     out = 4.7f * a * CFG::orbitScale;
    if (a < 60.0f) {
        out = 3.0f * a * CFG::orbitScale;
    } else {
        // out = a * (1.0f - 0.7f);
        out = (120.0f + a) * CFG::orbitScale;
        // OUT::motorAcc.motEn = false;
        // out = 0;
    }

    return s * out;
}


namespace Prim {
    void chase_ball() {
        
        // float rotAng = constrain(IN::ball.angle * 0.5f, -30, 30);
        // Motion::rotate_ToNField(rotAng, ST::pid.normalPIDCfg, 1.0f);
        
        Motion::rotate_ToNField(0.0f, ST::pid.normalPIDCfg);
        
        float finalAngle;
        bool close;
        if(IN::ball.proximity >= CFG::closeProximity) {
            close = true;
        }


        if(close) {
            finalAngle = closeOrbitAngle(IN::ball.angle, IN::ball.proximity);
            Motion::addMotion(finalAngle, 0.2f);

        } else {
            finalAngle = IN::ball.angle;
            Motion::addMotion(finalAngle, 0.2f);
        }



        // if (IN::ball.angle_ToNField == 0) {
        //     finalAngle = IN::ball.angle_ToNField;
        // } else if (IN::ball.angle_ToNField < 11 && IN::ball.proximity > 1) {
        //     finalAngle = int(2 * IN::ball.angle_ToNField * IN::ball.proximity * CFG::orbitScale);
        // } else if (IN::ball.angle_ToNField > 349 && IN::ball.proximity > 1) {
        //     int pomocAng = 360 - IN::ball.angle_ToNField;
        //     int kv_finalAngle = int(2 * pomocAng * IN::ball.proximity * CFG::orbitScale);
        //     finalAngle = 360 - kv_finalAngle;
        // } else if (IN::ball.angle_ToNField < 21 && IN::ball.proximity > 1) {
        //     finalAngle = int(2.7 * IN::ball.angle_ToNField * IN::ball.proximity * CFG::orbitScale);
        // } else if (IN::ball.angle_ToNField > 339 && IN::ball.proximity > 1) {
        //     int pomocAng = 360 - IN::ball.angle_ToNField;
        //     int kv_finalAngle = int(2.7 * pomocAng * IN::ball.proximity * CFG::orbitScale);
        //     finalAngle = 360 - kv_finalAngle;
        // } else if (IN::ball.angle_ToNField < 60 && IN::ball.proximity > 1) {
        //     finalAngle = int(2 * IN::ball.angle_ToNField * IN::ball.proximity * CFG::orbitScale);
        // } else if (IN::ball.angle_ToNField > 300 && IN::ball.proximity > 1) {
        //     int pomocAng = 360 - IN::ball.angle_ToNField;
        //     int kv_finalAngle = int(2 * pomocAng * IN::ball.proximity * CFG::orbitScale);
        //     finalAngle = 360 - kv_finalAngle;
        // } else if (IN::ball.angle_ToNField > 179) {
        //     finalAngle = int(IN::ball.angle_ToNField / IN::ball.proximity);
        // } else if (IN::ball.angle_ToNField < 180) {
        //     int pomocAng = 360 - IN::ball.angle_ToNField;
        //     int kv_finalAngle = int(pomocAng / IN::ball.proximity);
        //     finalAngle = 360 - kv_finalAngle;
        // }
        // Motion::addMotion_ToNField(finalAngle, 0.2f);



        #if DEBUG_FINALANGLE 
            Serial.print(">Ang: ");
            Serial.println(finalAngle);
        #endif

        // Motion::addMotion(IN::ball.angle, 0.2f);



        // Motion::rotate_ToNField(0.0f, ST::pid.normalPIDCfg, 1.0f);
        // Motion::addMotion(IN::ball.angle, 0.2f);
    }
}