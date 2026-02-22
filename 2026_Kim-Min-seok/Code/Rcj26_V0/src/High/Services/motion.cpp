#include "High/Services/motion.h"
#include "High/Services/motion_angles.h"
#include "math.h"

static int motion_wrap360(int16_t a) {
    while(a < 0) a += 360;
    while(a > 360) a -= 360;
    return a;
}


void addMotion(float angle, float weight) {
    
    int16_t a = (uint16_t)lround(angle);
    a = motion_wrap360(a);

    OUT::motorAcc.mainOut[0] += motionAngles[a][0] * weight;
    OUT::motorAcc.mainOut[1] += motionAngles[a][1] * weight;
    OUT::motorAcc.mainOut[2] += motionAngles[a][2] * weight;
    OUT::motorAcc.mainOut[3] += motionAngles[a][3] * weight;
}


void addRotation(float omega) {
    OUT::motorAcc.mainOut[0] -= omega;
    OUT::motorAcc.mainOut[1] += omega;
    OUT::motorAcc.mainOut[2] += omega;
    OUT::motorAcc.mainOut[3] -= omega;
}