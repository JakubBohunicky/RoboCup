#pragma once
#include <cstdint>

namespace ST {
    namespace Types {
        enum class goal_t : uint16_t { Yellow = 0, Blue = 1 }; 
        enum class mode_t : int8_t {Off = 0, Soccer = 1, Test = 2}; 
        enum class role_t : int8_t {Attacker = 0, Defender = 1, Test = 2}; 
        enum class menu_t : int8_t {None = -1, SetGoal = 0, SetRole = 1, SetSpeed = 2};
        enum class pid_t : int8_t {Slow = 0, Normal = 1, Fast = 2}; 
        struct pidCfg_t {
            float P;
            float D;
            float maxLimit;
        };
    }
}

namespace _Raw {

    struct ST_State {
        ST::Types::mode_t mode;
        ST::Types::mode_t mode_previous;
        uint32_t lastSoccerTime;
    };

    struct ST_PID {
        ST::Types::pidCfg_t fastPIDCfg;
        ST::Types::pidCfg_t normalPIDCfg;
        ST::Types::pidCfg_t slowPIDCfg;
        float PID_sumP;
        float PID_sumD;
        float PID_out;
        float PID_lastErr;
        uint16_t PID_dt_last_ms;
    };

    struct ST_Attacker {
      bool lineBounceFeature;
      uint32_t lineBounceFeatureTime;
    };

    struct ST_Soccer {
        ST::Types::role_t role;
        ST::Types::goal_t enemyGoal;
        float baseSpeed;
    };

    struct ST_OffMenu {
        ST::Types::menu_t state;
        ST::Types::menu_t cursor;
    };

    struct Comms_MSG {
        uint8_t version;
        uint8_t robotId;
        uint8_t mode;
        uint8_t hasBall;

        uint32_t seq;
        uint32_t uptimeMs;

        uint8_t seesBall;
        uint8_t reserved1;
        uint16_t reserved2;
    };

    struct Comms {
        uint8_t PEER_MAC[6];


        bool initialized = false;
        bool online = false;

        Comms_MSG rx_msg = {};
        Comms_MSG tx_msg = {};

        volatile bool lastSendOk = false;
        volatile bool sendDone = false;
        volatile bool newRxPacket = false;
        uint32_t lastRxMsg_ms = 0;
        uint32_t lastTxMsg_ms = 0;

        uint32_t txSeq = 0;

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