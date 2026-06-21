#include "High/Roles/role_defender.h"
#include "High/Roles/role_attacker.h"
#include "High/Roles/Primitives/prims.h"
#include "High/Services/motion.h"
#include "High/config_app.h"

static uint32_t hasBallLastTime = 0;
static uint32_t hadBallForTime = 0;

namespace Role {
    void defender() {

        if(ST::soccer.defender.startedOnLine) {
            Motion::dribler(1);

            if(!IN::motionSens.hasBall) {
                hadBallForTime = ST::now_ms;
            }

            if(ST::now_ms - hadBallForTime >= 100 || (ST::soccer.defender.attacking && !ST::soccer.defender.defending)) {
                // Prim::find_goal();
                ST::soccer.attacker.changed_role = true;
                ST::soccer.attacker.changed_role_time = ST::now_ms;
                ST::soccer.defender.attacking = true;
                ST::soccer.defender.defending = false;
                Role::attacker();
                if(IN::motionSens.hasBall){
                    hasBallLastTime = ST::now_ms;
                } else if (ST::now_ms - hasBallLastTime >= 2000) {
                    ST::soccer.defender.attacking = false;
            }

            } else {
                if(ST::soccer.defender.defending) {
                    Prim::defend_goal();
                } else {
                    ST::soccer.defender.defending = true;
                    ST::soccer.defender.attacking = false;
                    ST::soccer.defender.startedOnLine = false;
                }
            }

        } else {
            Motion::dribler(0);
             if(IN::line.seen) {
                if(IN::goalOur.seen) {
                if(IN::goalOur.angle >= -Const::Attacker::shootAngle && IN::goalOur.angle <= Const::Attacker::shootAngle) { 
                    ST::soccer.defender.startedOnLine = IN::line.seen;
                    // OUT::led_Debug.needsUpdate = true;
                    // OUT::led_Debug.color[1] = CRGB::Black;
                    Motion::rotate_ToNField(0.0f, ST::pid.normalPIDCfg);
                } else {
                    Prim::defender_find_our_goal();
                }
            } else {
                Prim::defender_find_our_goal();
            }
            } else {
                Prim::defender_find_our_goal();
            }
        }
    }
}
