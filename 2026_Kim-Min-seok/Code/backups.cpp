        if (IN::ball.angle_ToNField == 0) {
            finalAngle = IN::ball.angle_ToNField;
        } else if (IN::ball.angle_ToNField < 11 && IN::ball.proximity > 1) {
            finalAngle = int(2 * IN::ball.angle_ToNField * IN::ball.proximity * CFG::orbitScale);
        } else if (IN::ball.angle_ToNField > 349 && IN::ball.proximity > 1) {
            int pomocAng = 360 - IN::ball.angle_ToNField;
            int kv_finalAngle = int(2 * pomocAng * IN::ball.proximity * CFG::orbitScale);
            finalAngle = 360 - kv_finalAngle;
        } else if (IN::ball.angle_ToNField < 21 && IN::ball.proximity > 1) {
            finalAngle = int(2.7 * IN::ball.angle_ToNField * IN::ball.proximity * CFG::orbitScale);
        } else if (IN::ball.angle_ToNField > 339 && IN::ball.proximity > 1) {
            int pomocAng = 360 - IN::ball.angle_ToNField;
            int kv_finalAngle = int(2.7 * pomocAng * IN::ball.proximity * CFG::orbitScale);
            finalAngle = 360 - kv_finalAngle;
        } else if (IN::ball.angle_ToNField < 60 && IN::ball.proximity > 1) {
            finalAngle = int(2 * IN::ball.angle_ToNField * IN::ball.proximity * CFG::orbitScale);
        } else if (IN::ball.angle_ToNField > 300 && IN::ball.proximity > 1) {
            int pomocAng = 360 - IN::ball.angle_ToNField;
            int kv_finalAngle = int(2 * pomocAng * IN::ball.proximity * CFG::orbitScale);
            finalAngle = 360 - kv_finalAngle;
        } else if (IN::ball.angle_ToNField > 179) {
            finalAngle = int(IN::ball.angle_ToNField / IN::ball.proximity);
        } else if (IN::ball.angle_ToNField < 180) {
            int pomocAng = 360 - IN::ball.angle_ToNField;
            int kv_finalAngle = int(pomocAng / IN::ball.proximity);
            finalAngle = 360 - kv_finalAngle;
        }
        Motion::addMotion_ToNField(finalAngle, 0.2f);







        
            if(IN::goalEnemy.seen) {
                if(IN::goalEnemy.angle >= -Const::Attacker::shootAngle && IN::goalEnemy.angle <= Const::Attacker::shootAngle) { 
                    // OUT::kicker_Drb.kickF = true; 
                    Motion::addMotion(IN::goalEnemy.angle, 0.2f);
                    Motion::rotate(IN::goalEnemy.angle, ST::pid.slowPIDCfg);
                }
                Motion::rotate(IN::goalEnemy.angle, ST::pid.slowPIDCfg);
            } else {
                Motion::addMotion_ToNField(0.0f, 0.2f);
                Motion::rotate_ToNField(0, ST::pid.slowPIDCfg); 
            }




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
