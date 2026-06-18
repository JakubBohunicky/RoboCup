#include "High/Roles/role_defender.h"
#include "High/Roles/Primitives/prims.h"
#include "High/Services/motion.h"


namespace Role {
    void defender() {

        Motion::dribler(0);

        // if(IN::motionSens.hasBall) {
        //     Prim::find_goal();
        // } else {
            Prim::defend_goal();
        // }
    }
}
