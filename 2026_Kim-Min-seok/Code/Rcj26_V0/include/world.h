#pragma once
#include <cstdint>


namespace _Raw {

    struct LED {
        uint8_t brightness = 0;
        uint32_t color = 0xFFFFFF;
    };

    struct KickerDrb
    {
        bool drbReverseDir = false;
        bool drbEn = false;
        bool kickF = false;
        bool kickR = false;
    };
    

    struct Goal {
        bool seen = false;
        float angle = 0.0f; //Angle from -180 to 180
        uint16_t size = 0;  //probably needs normalisartion
    };


    struct Gyro {
        float offset = 0.0f;
        float offset_ToNField = 0.0f;
        uint8_t calSys = 0; //3 is most precise
        uint8_t calGyr = 0;
        uint8_t calAcl = 0;
        uint8_t calMag = 0; 
    };

        struct Ball {
        int16_t angle = 0; 
        int16_t angle_ToNField = 0;
        uint16_t distRaw = 0; //higher number is means the ball is further away
        float strength = 0.0f; //from 1-closest to 0-furthest 
        
    };

    struct Line {
        int16_t angle = 0; //Angle of the (NOT THE ESCAPE ANGLE!)
        bool seen = false;
        float depth = 0.0f;  //Dept 0.0f means the robot is not on the line
    };

    struct motionSense {
        float motSpeed = 0.0f;
        float drbSpeed = 0.0f;
        bool drbR = false;
        bool drbF = false;
    };

}



namespace IN {
    extern _Raw::Goal goalEnemy;
    extern _Raw::Goal goalOur;
    extern _Raw::Gyro gyro;
    extern _Raw::Ball ball;
    extern _Raw::Line line;
    extern _Raw::motionSense motionSens;
}

namespace OUT {
    extern _Raw::LED led_O; //brightnes je globalna cize plati len pre LED_O ziadna ina
    extern _Raw::LED led_X;
    extern _Raw::LED led_Debug;
    extern _Raw::KickerDrb kicker_Drb;
}


namespace STATE {

}







