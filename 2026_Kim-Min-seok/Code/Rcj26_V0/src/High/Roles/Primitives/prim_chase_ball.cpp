#include "High/Roles/Primitives/prim_chase_ball.h"
#include "High/Services/motion.h"

namespace Prim {
    void chase_ball() {
        // Motion::rotate_ToNField(IN::ball.angle, ST::pid.normalPIDCfg, 0.01f);
        Motion::rotate_ToNField(0.0f, ST::pid.normalPIDCfg, 0.01f);
        Motion::addMotion(IN::ball.angle, 0.2f);
    }
}