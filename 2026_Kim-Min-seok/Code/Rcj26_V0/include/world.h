#pragma once
#include "High/config_app.h"
#include <cstdint>


namespace _Raw {

    enum class goal_t : uint8_t {
        Yellow = ,
        Blue = 
    };

    struct Display {
        bool needsUpdate = true;
    };

    struct MotorAcc {
        float mainOut[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        bool motEn = false;

    };

    struct LED {
        bool needsUpdate = true;
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
    
    struct Generic
    {
        bool bukajModuleEn = false;
        bool btnPlusClick = false;
        bool btnMinusClick = false;
        bool btnPlusLongPress = false;
        bool btnMinusLongPress = false;
        bool btnPlusIsDown = false;
        bool btnMinusIsDown = false;
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
        int16_t angle = 0; //Angle to the line (NOT THE ESCAPE ANGLE!)
        int16_t angle_ToNField = 0; // -||-
        bool seen = false;
        float depth = 0.0f;  //Dept 0.0f means the robot is not on the line
    };

    struct MotionSense {
        float motSpeed = 0.0f;
        float drbSpeed = 0.0f;
        bool drbR = false;
        bool drbF = false;
    };


    struct Robot {
        bool Goal_attackOnBlue = true; 
        
    };
}


namespace IN {
    extern _Raw::Goal goalEnemy;
    extern _Raw::Goal goalOur;
    extern _Raw::Gyro gyro;
    extern _Raw::Ball ball;
    extern _Raw::Line line;
    extern _Raw::MotionSense motionSens;
    extern _Raw::Generic generic;
}

namespace OUT {
    extern _Raw::LED led_O; //brightnes je globalna cize plati len pre LED_O ziadna ina
    extern _Raw::LED led_X;
    extern _Raw::LED led_Debug;
    extern _Raw::Display display;
    extern _Raw::KickerDrb kicker_Drb;
    extern _Raw::MotorAcc motorAcc; //motor output accumulator
}


namespace ST {
    extern _Raw::Robot robot;
}







