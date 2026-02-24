#pragma once
#include "robot_types.h"


namespace ST_Default {

    inline const _Raw::ST_State state = {
        .mode = ST::Types::mode_t::Off,
        .role = ST::Types::role_t::Attacker
    };

    inline const _Raw::ST_Soccer soccer = {
        .enemyGoal = ST::Types::goal_t::Yellow,
        .baseSpeed = 1.0f
    };
}

//DEBUG
constexpr bool STOP_MOTORS = 0;
constexpr bool DISPLAY_DEBUG = 0;