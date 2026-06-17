#include "High/Roles/Primitives/prim_chase_ball.h"
#include "High/Services/motion.h"
#include "Low/inputs.h"
#include "High/Services/debug.h"
#include "Low/Outputs/output_display.h"

namespace CFG {
    static constexpr float closeProximity = 0.9f;

    static constexpr float FRONT_ZONE_DEG  = 90.0f;   // aktívna zóna +-stupne
}

float closeOrbitAngle(float ballAngle, float proximity) {
    float a = fabs(ballAngle);

    static constexpr float FRONT_ZONE_DEG   = CFG::FRONT_ZONE_DEG;
    static constexpr float FRONT_OFFSET_K   = 55.0f;
    static constexpr float BACK_TARGET_180  = 80.0f;
    static constexpr float orbitScale       = 1.0f;

    proximity = constrain(proximity, 0.0f, 1.0f);

    // PREDOK POD 90° - NIC NEMENENE
    if (a <= FRONT_ZONE_DEG) {
        float rad = deg2rad(ballAngle);
        float offset = FRONT_OFFSET_K * sinf(rad) * (0.6f + 0.4f * proximity);
        return wrap180((ballAngle + offset) * orbitScale);
    }
    else if (a > 90.0f && a <= 135.0f) {
        float t = (a - 90.0f) / 45.0f;   // 90 -> 0, 135 -> 1
        t = t * t * (3.0f - 2.0f * t);   // smoothstep

        float targetAbs = 180.0f - t * 45.0f;   // 180 -> 135

        float target;
        if (ballAngle > 0.0f) {
            target = targetAbs;
        } else {
            target = -targetAbs;
        }

        return wrap180(target);
    }

    else if (a > 135.0f && a <= 180.0f) {
        float t = (a - 135.0f) / 45.0f;   // 135 -> 0, 180 -> 1

        float targetAbs = 135.0f - t * 45.0f;   // 135 -> 90

        float target;
        if (ballAngle > 0.0f) {
            target = -targetAbs;   // opacna strana ako lopta
        } else {
            target = targetAbs;    // opacna strana ako lopta
        }

        return wrap180(target);
    }
    else {
        return 999;
    }
}

namespace Prim {
    void chase_ball() {
        
        float rotAng = constrain(IN::ball.angle * 0.5f, -30, 30);
        Motion::rotate_ToNField(rotAng, ST::pid.normalPIDCfg, 1.0f);


        
        // Motion::rotate_ToNField(0.0f, ST::pid.normalPIDCfg);
        
        float finalAngle;
        if(IN::ball.seen) {
            
            bool close = false;
            if(IN::ball.proximity >= CFG::closeProximity) {
                close = true;
            }


            if(close) {
                finalAngle = closeOrbitAngle(IN::ball.angle, IN::ball.proximity);
                if(finalAngle != 999) {
                    Motion::addMotion(finalAngle, 0.4f);
                }

            } else {
                finalAngle = IN::ball.angle;
                Motion::addMotion(finalAngle, 0.5f);
            }

        } else{
            finalAngle = 999;
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
            Serial.print(finalAngle);

            Serial.print(" ||  >BAng: ");
            Serial.println(IN::ball.angle);
        #endif


        #if DEBUG_DISPLAY_FINAL_ANGLE
            if(OUT::display.needsUpdate) { 

                display.setTextSize(1);
                display.setCursor(3, 37);
                display.print("F_Ang:");
                display.setCursor(41, 37);
                display.print(finalAngle);
            }
        #endif

        // Motion::addMotion(IN::ball.angle, 0.2f);



        // Motion::rotate_ToNField(0.0f, ST::pid.normalPIDCfg, 1.0f);
        // Motion::addMotion(IN::ball.angle, 0.2f);
    }
}