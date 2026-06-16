#include "High/Roles/Primitives/prim_chase_ball.h"
#include "High/Services/motion.h"
#include "Low/inputs.h"
#include "High/Services/debug.h"
#include "Low/Outputs/output_display.h"

namespace CFG {
    static constexpr float closeProximity = 0.8f;

    static constexpr float FRONT_ZONE_DEG  = 90.0f;   // aktívna zóna +-stupne
}

// vracia finalAngle pre addMotion_ToNField
// ballAngle = IN::ball.angle (signed, -180..180)
// vracia float v -180..180
float closeOrbitAngle(float ballAngle, float proximity) {
    float a = fabs(ballAngle);

    if (a > CFG::FRONT_ZONE_DEG) {
        return 999;       // mimo zony - nerob nic, riadenie prebera iny kod
    }

    static constexpr float FRONT_OFFSET_K  = 55.0f;   // sila orbitu, 0 = rovno, 90 = max uhol
    static constexpr float orbitScale = 1.0f;
    float rad = deg2rad(ballAngle);
    float offset = FRONT_OFFSET_K * sinf(rad);

    return wrap180((ballAngle + offset) * orbitScale);
}

// float closeOrbitAngle(float ballAngle, float proximity) {
//     float rad = deg2rad(ballAngle);
//     float orbitAngle = ballAngle + 90.0f * sinf(rad);
//     return wrap180(orbitAngle * CFG::orbitScale);
// }

// float closeOrbitAngle(float ballAngle, float proximity) {
//     float a = fabs(ballAngle);
//     float s = (ballAngle >= 0.0f) ? 1.0f : -1.0f;
//     float out = ballAngle;

//     // lopta vpredu -> jemne do radlice
//     if (a < 8.0f) {
//         out = ballAngle;
//     } 
//     else if (a < 20.0f) {
//         out = ballAngle + s * 6.0f;
//     } 
//     else if (a < 35.0f) {
//         out = ballAngle + s * 12.0f;
//     } 
//     else if (a < 55.0f) {
//         out = ballAngle + s * 22.0f;
//     } 
//     else if (a < 80.0f) {
//         out = ballAngle + s * 28.0f;
//     } 
//     else if (a < 110.0f) {
//         out = ballAngle + s * 40.0f;
//     } 
//     else if (a < 140.0f) {
//         out = ballAngle + s * 50.0f;
//     } 
//     // lopta za robotom -> obísť ju dopredu
//     else {
//         float behindOffset = 55.0f;

//         if (proximity > 0.75f) {
//             behindOffset = 40.0f;
//         } else if (proximity > 0.55f) {
//             behindOffset = 48.0f;
//         }

//         out = s * (90.0f - behindOffset);
//     }

//     return wrap180(out * CFG::orbitScale);
// }



// float closeOrbitAngle(float ballAngle, float proximity) {
//     float proxOld = 1.0f + 0.5f * proximity;   // 0..1 -> 1..1.5

//     float s = (ballAngle >= 0.0f) ? 1.0f : -1.0f;
//     float a = fabs(ballAngle);
//     float out = 0.0f;

//     if (a == 0.0f) {
//         out = 0.0f;
//     } else if (a < 11.0f && proxOld > 1.0f) {
//         out = 2.0f * a * proxOld * CFG::orbitScale;
//     } else if (a < 21.0f && proxOld > 1.0f) {
//         out = 2.7f * a * proxOld * CFG::orbitScale;
//     } else if (a < 60.0f && proxOld > 1.0f) {
//         out = 2.0f * a * proxOld * CFG::orbitScale;
//     } else {
//         out = a / proxOld;
//     }

//     return wrap180(s * out);
// }

namespace Prim {
    void chase_ball() {
        
        // float rotAng = constrain(IN::ball.angle * 0.5f, -30, 30);
        // Motion::rotate_ToNField(rotAng, ST::pid.normalPIDCfg, 1.0f);


        
        Motion::rotate_ToNField(0.0f, ST::pid.normalPIDCfg);
        
        float finalAngle;
        if(IN::ball.seen) {
            
            bool close;
            if(IN::ball.proximity >= CFG::closeProximity) {
                close = true;
            }


            if(close) {
                finalAngle = closeOrbitAngle(IN::ball.angle, IN::ball.proximity);
                if(finalAngle != 999) {
                    Motion::addMotion(finalAngle, 0.2f);
                }

            } else {
                finalAngle = IN::ball.angle;
                Motion::addMotion(finalAngle, 0.2f);
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