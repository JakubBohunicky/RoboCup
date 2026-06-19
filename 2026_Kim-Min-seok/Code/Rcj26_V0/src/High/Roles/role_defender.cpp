#include "High/Roles/role_defender.h"
#include "High/Roles/Primitives/prims.h"
#include "High/Services/motion.h"
#include "High/config_app.h"


namespace Role {
    void defender() {

        if(ST::soccer.defender.startedOnLine) {

            Motion::dribler(1);
        // if(IN::motionSens.hasBall) {
        //     Prim::find_goal();
        // } else {
            Prim::defend_goal();
        // }

        } else {
            Motion::dribler(0);
             if(IN::line.seen) {
                if(IN::goalOur.seen) {
                if(IN::goalOur.angle >= -Const::Attacker::shootAngle && IN::goalEnemy.angle <= Const::Attacker::shootAngle) { 
                    ST::soccer.defender.startedOnLine = IN::line.seen;
                    OUT::led_Debug.needsUpdate = true;
                    OUT::led_Debug.color[1] = CRGB::Black;
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
