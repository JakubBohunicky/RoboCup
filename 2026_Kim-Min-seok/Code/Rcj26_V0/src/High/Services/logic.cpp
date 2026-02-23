#include "High/Services/logic.h"
#include "High/Modes/mode_soccer.h"
#include "High/Modes/mode_off.h"
#include "High/Modes/mode_test.h"



namespace Logic {

    void determineMode() {
        if(ST::state.mode != ST::Types::mode_t::Off) { //Robot is playing
            if(IN::generic.btnPlusIsDown || IN::generic.btnMinusIsDown)
            {
                ST::state.mode = ST::Types::mode_t::Off;
            }
        }
        else if(ST::state.mode != ST::Types::mode_t::Test) { //Robot is in test mode
            if(IN::generic.btnPlusIsDown || IN::generic.btnMinusIsDown)
            {
                ST::state.mode = ST::Types::mode_t::Off;
            }
        }
    }


    void applyMode() {
        // if(ST::state.mode == ST::Types::mode_t::Soccer) Mode::soccer();
        // else if(ST::state.mode == ST::Types::mode_t::Test) Mode::test();
        /*else*/ if(ST::state.mode == ST::Types::mode_t::Off) Mode::off();
    }
}