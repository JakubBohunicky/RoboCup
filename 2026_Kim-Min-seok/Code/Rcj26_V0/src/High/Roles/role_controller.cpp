#include "High/Roles/role_controller.h"
#include "High/Services/motion.h"
// #include "High/config_app.h"


namespace Role {
    void controller() {

        Motion::addMotion_ToNField(IN::controller.lStick.angle, IN::controller.lStick.mag * (0.5f + 0.5f * IN::controller.r2.val - 0.5f * IN::controller.l2.val));
        Motion::rotate_ToNField(IN::controller.rStick.angle, ST::pid.normalPIDCfg, IN::controller.rStick.mag * (0.5f + 0.5f * IN::controller.r2.val - 0.5f * IN::controller.l2.val));

        if(IN::controller.r1.Click) {
            Motion::kickFront();
        }
        if(IN::controller.l1.Click) {
            Motion::kickRear();
        }
        //vediet zmenit farku robota

    }
}
