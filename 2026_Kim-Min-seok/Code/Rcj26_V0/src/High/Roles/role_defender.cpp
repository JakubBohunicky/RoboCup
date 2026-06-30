#include "High/Roles/role_defender.h"
#include "High/Roles/role_attacker.h"
#include "High/Roles/Primitives/prims.h"
#include "High/Services/motion.h"
#include "High/config_app.h"
#include "High/Modes/mode_soccer.h"
#include "High/Services/debug.h"
#include "Low/inputs.h"


namespace Role {
    void defender() {

        

        if(ST::soccer.defender.changed_role) {

            if(ST::now_ms - ST::soccer.defender.changed_role_time >= 350){
                ST::soccer.defender.changed_role = false;
            }
            Motion::rotate_ToNField(0.0f, ST::pid.normalPIDCfg);
            Motion::addMotion_ToNField(180.0f, 0.4f);

        } else {


            if(ST::soccer.defender.startedOnLine) {


                Motion::dribler(1);

                if(ST::now_ms - IN::motionSens.heldBallFor_ms >= 100) {
                    Role::changeRole();
                    #if !ENABLE_BALL_ROLE_CHANGE_BACK
                        IN::comms.soccer_send_code = 1;
                    #endif
                } else {
                    if(ST::soccer.defender.defending) {
                        Prim::defend_goal();
                    } else {
                        // ST::soccer.defender.defending = true;
                        ST::soccer.defender.attacking = false;
                        ST::soccer.defender.startedOnLine = false;
                    }
                }

            } else {
                Motion::dribler(0);
                if(IN::line.seen) {
                    if(ST::now_ms - IN::pixyRear.goalOur.lastSeen_ms <= 500) {
                    // if(IN::pixyRear.goalOur.angle >= -(Const::Attacker::shootAngle + 180.0f) && IN::pixyRear.goalOur.angle <= Const::Attacker::shootAngle -180.0f) { 
                        ST::soccer.defender.startedOnLine = IN::line.seen;
                        // OUT::led_Debug.needsUpdate = true;
                        // OUT::led_Debug.color[1] = CRGB::Black;
                        Motion::rotate_ToNField(0.0f, ST::pid.normalPIDCfg);
                    // } else {
                    //     Prim::defender_find_our_goal();
                    // }
                } else {
                    Prim::defender_find_our_goal();
                }
                } else {
                    Prim::defender_find_our_goal();
                }
            }
        }
    }
}
