#include "High/Roles/Primitives/prim_avoid_line.h"
#include "High/Services/motion.h"


namespace Prim {
    void avoid_line() {
        Motion::addMotion(IN::line.angle + 180.f, IN::line.depth*2);
    }
}