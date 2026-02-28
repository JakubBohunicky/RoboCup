#include "High/Services/logic.h"
#include "High/Modes/mode_soccer.h"
#include "High/Modes/mode_off.h"
#include "High/Modes/mode_test.h"
#include "Low/Inputs/input_gyro.h"
#include <Arduino.h>




namespace Logic {

    void determineMode() {

        if(ST::state.mode == ST::Types::mode_t::Soccer) {
            if(IN::generic.btnPlusIsDown || IN::generic.btnMinusIsDown) {
                ST::state.mode = ST::Types::mode_t::Off;
                ST::state.lastSoccerTime = millis();
            }
        }

        else if(ST::state.mode == ST::Types::mode_t::Off) {
            if(ST::offMenu.state != ST::Types::menu_t::SetSpeed) {
                if(IN::generic.btnPlusClick && millis() - ST::state.lastSoccerTime >= 1000) {
                    ST::state.mode = ST::Types::mode_t::Soccer;            
                }
                if(IN::generic.btnMinusLongPress) {
                    // input_gyro_calibrate();
                    IN::gyro.offset = random (-180, 180);
                }
                if(IN::generic.btnMinusClick) {
                    switch (ST::offMenu.cursor) {
                    case ST::Types::menu_t::SetGoal: 
                        ST::offMenu.cursor = ST::Types::menu_t::SetRole;
                        break;

                    case ST::Types::menu_t::SetRole: 
                        ST::offMenu.cursor = ST::Types::menu_t::SetSpeed;
                        break;
                    
                    case ST::Types::menu_t::SetSpeed: 
                        ST::offMenu.cursor = ST::Types::menu_t::SetGoal;
                        break;
                    default:
                        ST::offMenu.cursor = ST::Types::menu_t::SetGoal;
                        break;
                    }
                }

                if(IN::generic.btnPlusLongPress) {
                    switch (ST::offMenu.cursor) {
                        case ST::Types::menu_t::SetGoal:
                            if(ST::soccer.enemyGoal == ST::Types::goal_t::Yellow) {
                                ST::soccer.enemyGoal = ST::Types::goal_t::Blue;
                            } else {
                                ST::soccer.enemyGoal = ST::Types::goal_t::Yellow;
                            } break;

                        case ST::Types::menu_t::SetRole:
                            if(ST::soccer.role == ST::Types::role_t::Attacker) {
                                ST::soccer.role = ST::Types::role_t::Defender;
                            } else {
                                ST::soccer.role = ST::Types::role_t::Attacker;
                            } break;

                        case ST::Types::menu_t::SetSpeed:
                            ST::offMenu.state = ST::Types::menu_t::SetSpeed;
                            break;
                        default:
                            break;
                    }
                }
            }

            else { //set speed menu
                if(IN::generic.btnPlusLongPress || IN::generic.btnMinusLongPress) ST::offMenu.state = ST::Types::menu_t::None;
                if(IN::generic.btnPlusClick) ST::soccer.baseSpeed +=0.05f;
                if(IN::generic.btnMinusClick) ST::soccer.baseSpeed -=0.05f;
            }
        }
    }


    void applyMode() {
        if(ST::state.mode == ST::Types::mode_t::Soccer) Mode::soccer();
        else if(ST::state.mode == ST::Types::mode_t::Off) Mode::off();
        // else if(ST::state.mode == ST::Types::mode_t::Test) Mode::test();
        ST::state.mode_previous = ST::state.mode;
    }
}