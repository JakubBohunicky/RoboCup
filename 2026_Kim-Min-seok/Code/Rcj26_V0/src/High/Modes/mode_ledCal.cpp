#include "High/Modes/mode_ledCal.h"
#include "Low/Outputs/output_display.h"
#include "High/Services/motion.h"

static int8_t _mot_state = 0;

static void _drawScreen() {
    OUT::display.needsUpdate = true;
    
    display.setTextColor(1);
    display.setTextWrap(false);
    display.setCursor(17, 1);
    display.print("...LED Cal...");

    display.setCursor(3, 17);
    display.print("Kicker");


    display.setTextSize(3);
    display.setCursor(30, 36);

    switch (_mot_state)
    {
    case 1:
        display.print("F");
        break;
    case -1:
        display.print("R");
        break;
    default:
        display.print("0");
        break;
    }

}


namespace Mode {
    void ledCal() {
        // ST::offMenu.screen = ST::Types::screen_t::Main;

        OUT::motorAcc.motEn = true;

        //!!!!avoid using: IN::generic.btnPlus.LongPress;

        if(_mot_state == 0) {
            if(IN::generic.btnPlus.Click) { _mot_state = -1; }
            if(IN::generic.btnMinus.Click) { _mot_state = 1; }
        } else {
             if(IN::generic.btnPlus.Click || IN::generic.btnMinus.Click) {
                _mot_state = 0;
             }
        }


        switch (_mot_state) {
        case 1:
            Motion::addMotion(90, 1.0f);
            Motion::dribler(1);
            break;
        case -1:
            Motion::addMotion(-90, 1.0f);
            Motion::dribler(1);
            break;
        default:
            Motion::dribler(0);
            break;
        }

        _drawScreen();

    }
}