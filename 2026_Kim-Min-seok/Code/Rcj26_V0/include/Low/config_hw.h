#pragma once


namespace HW {

    namespace Motor {
    //MOTORS
    constexpr int EnPin = 38;
    constexpr int A_DirPin = 42;
    constexpr int A_PwmPin = 41;
    constexpr int B_DirPin = 48;
    constexpr int B_PwmPin = 47;
    constexpr int C_DirPin = 14;
    constexpr int C_PwmPin = 13;
    constexpr int D_DirPin = 12;
    constexpr int D_PwmPin = 11;
    //DRIBLER
    constexpr int DRB_DirPin = 2;
    constexpr int DRB_PwmPin = 10;
    //KICKER
    constexpr int Kicker_F_Pin = 7;
    constexpr int KICKER_R_Pin = 21;

    //MOTOR PWM PARAMETERS
    constexpr int PWM_Freq = 1000; //1kHz
    constexpr int PWM_Resolution = 10; //10bit
    }

    namespace MotorSense{
    //MOTORS SENSE
    constexpr int DRBF_Spd_Pin = 1;
    constexpr int A_Spd_Pin = 15;
    constexpr int B_Spd_Pin = 16;
    constexpr int C_Spd_Pin = 17;
    constexpr int D_Spd_Pin = 18;

    //SWITCHES
    constexpr int DRB_SW_F_Pin = 40;
    constexpr int DRB_SW_R_Pin = 39;
    }



    namespace GENERIC {
        //BUTTONS
        constexpr int BTN_inc_Pin = 20;
        constexpr int BTN_dec_Pin = 19;
        //BUKAJ MODUL
        constexpr int BukajModule_Pin = 35;
        //I2C
        constexpr int I2C_SDA_Pin = 8;
        constexpr int I2C_SCL_Pin = 9;
    }

    namespace LINE{
        //LED AND LINE MUX
        constexpr int LedSet0_Pin = 36;
        constexpr int LedSet_Xdebug_Pin = 37;
        constexpr int Line_A_Read_Pin = 4;
        constexpr int Line_B_Read_Pin = 5;
        constexpr int Line_X_Read_Pin = 6;
        constexpr int LineSet0_Pin = 0;
        constexpr int LineSet1_Pin = 45;
        constexpr int LineSet2_Pin = 46;
        constexpr int LineSet3_Pin = 3;
    }


    namespace BallCfg {
        constexpr int IR_ADR = 0x10;
        constexpr int IR_REG = 0x00;

        constexpr int c_ballEffectiveInputClosest = 2500;
        constexpr int c_ballEffectiveInputFurthes = 2100;
    }

    namespace PixyCfg {
        constexpr int c_pixy_frameWidth = 316;  //camera pixel width
        constexpr int c_pixy_frameHeight = 208; //camera pixel height
        constexpr int c_pixy_objMinHeight = 108; //minimum height of object to be detected
        constexpr float c_pixy_FOV = 60.0f;

        constexpr int c_GoalSigEnemy = 1;   //Signatures from PixyMon 
        constexpr int c_GoalSigOur = 2;

    }

}

