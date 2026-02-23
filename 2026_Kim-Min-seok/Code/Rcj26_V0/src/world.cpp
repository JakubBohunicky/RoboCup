#include "world.h"
#include "High/config_app.h"

namespace IN {
    _Raw::Goal goalEnemy;
    _Raw::Goal goalOur;
    _Raw::Gyro gyro;
    _Raw::Ball ball;
    _Raw::Line line;
    _Raw::MotionSense motionSens;
    _Raw::Generic generic;
}

namespace OUT {
    _Raw::LED led_O; //brightnes je globalna cize plati len pre LED_O ziadna ina
    _Raw::LED led_X;
    _Raw::LED led_Debug;
    _Raw::Display display;
    _Raw::KickerDrb kicker_Drb;
    _Raw::MotorAcc motorAcc;
}

namespace ST {
    _Raw::ST_State state;
    _Raw::ST_Soccer soccer;
    
    void resetToDefaults() {
        state = ST_Default::state;
        soccer = ST_Default::soccer;
    }
}