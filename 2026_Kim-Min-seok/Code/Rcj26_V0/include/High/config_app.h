#pragma once
#include "robot_types.h"



namespace ST_Default {

    inline const _Raw::ST_Mode mode = {
        .mode = Types::mode_t::Off
    };

    inline const _Raw::ST_Soccer soccer = {
        .enemyGoal = Types::goal_t::Yellow,
        .baseSpeed = 1.0f
    };
}

//DEBUG
constexpr bool STOP_MOTORS = 0;
constexpr bool DISPLAY_DEBUG = 0;