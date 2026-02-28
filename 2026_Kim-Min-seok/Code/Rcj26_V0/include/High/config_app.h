#pragma once
#include "robot_types.h"


namespace ST_Default {

    inline const _Raw::ST_State state = {
        .mode = ST::Types::mode_t::Off,
        .mode_previous = ST::Types::mode_t::Off,
        .lastSoccerTime = 0
    };

    inline const _Raw::ST_Soccer soccer = {
        .role = ST::Types::role_t::Attacker,
        .enemyGoal = ST::Types::goal_t::Yellow,
        .baseSpeed = 1.0f
    };

    inline const _Raw::ST_OffMenu offMenu = {
        .state = ST::Types::menu_t::None,
        .cursor = ST::Types::menu_t::SetGoal
    };
}

//DEBUG
constexpr bool STOP_MOTORS = 0;
constexpr bool DISPLAY_DEBUG = 0;