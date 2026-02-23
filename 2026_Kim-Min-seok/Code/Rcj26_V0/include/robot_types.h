#pragma once
#include <cstdint>

namespace ST {
    namespace Types {
        enum class goal_t : uint16_t { Yellow = 0, Blue = 1 }; 
        enum class mode_t : int8_t {Off = 0, Soccer = 1, Test = 2}; 
        enum class role_t : int8_t {Attacker = 0, Defender = 1, Test = 2}; 
    }
}

namespace _Raw {

    struct ST_State {
        ST::Types::mode_t mode;
        ST::Types::role_t role;
    };

    struct ST_Soccer {
        ST::Types::goal_t enemyGoal;
        float baseSpeed;
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
}