#include "High/Roles/role_attacker.h"
#include "High/Roles/Primitives/prim_avoid_line.h"
#include "High/Roles/Primitives/prim_chase_ball.h"
#include "High/Roles/Primitives/prim_find_goal.h"
#include "High/Services/motion.h"
#include "High/config_app.h"

uint32_t testTime1 = 0;
bool test_fw = true;

namespace Role {
    void attacker() {


        if(ST::now_ms - testTime1 >= 1000) {
            testTime1 = ST::now_ms;
            test_fw = !test_fw;
        }
        
        if(test_fw) {
                Motion::addMotion(0.0f , 1.0f);
            } else {
                Motion::addMotion(180.0f , 1.0f);
        }

        // if(IN::motionSens.drbF || IN::motionSens.drbR) {
        //     Prim::find_goal();
        // }
        
        // else {
        //     Prim::chase_ball();
        // }

    }
}



//  if(IN::line.seen) {
//             Motion::addMotion(IN::line.angle + 180, Motion::weight_Hard * IN::line.depth * (1.0f + IN::motionSens.motSpeed));
//         }