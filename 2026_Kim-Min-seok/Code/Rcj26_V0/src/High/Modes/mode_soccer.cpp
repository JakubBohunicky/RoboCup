#include "High/Modes/mode_soccer.h"
#include "High/Roles/role_attacker.h"
#include "High/Roles/role_defender.h"
#include "Low/Outputs/output_display.h"
#include "High/Services/debug.h"

static constexpr unsigned char PROGMEM image_EviSmile1_bits[] = {0x0f,0x00,0x00,0x0f,0x00,0x0f,0x00,0x00,0x0f,0x00,0x3c,0x00,0x00,0x03,0xc0,0x3c,0x00,0x00,0x03,0xc0,0xfc,0x00,0x00,0x03,0xf0,0xfc,0x00,0x00,0x03,0xf0,0xff,0x0f,0xff,0x0f,0xf0,0xff,0x0f,0xff,0x0f,0xf0,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xf0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0xfc,0xff,0xff,0xf3,0xf0,0xfc,0xff,0xff,0xf3,0xf0,0xfc,0x3f,0xff,0xc3,0xf0,0xfc,0x3f,0xff,0xc3,0xf0,0xfc,0x0f,0xff,0x03,0xf0,0xfc,0x0f,0xff,0x03,0xf0,0xfc,0x03,0xfc,0x03,0xf0,0xfc,0x03,0xfc,0x03,0xf0,0xff,0x03,0xfc,0x0f,0xf0,0xff,0x03,0xfc,0x0f,0xf0,0xff,0xff,0xff,0xff,0xf0,0xff,0xff,0xff,0xff,0xf0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xff,0xff,0xff,0xc0,0x3f,0xcf,0xff,0x3f,0xc0,0x3f,0xcf,0xff,0x3f,0xc0,0x0f,0xf3,0x0c,0xff,0x00,0x0f,0xf3,0x0c,0xff,0x00,0x03,0xfc,0x03,0xfc,0x00,0x03,0xfc,0x03,0xfc,0x00,0x00,0xff,0xff,0xf0,0x00,0x00,0xff,0xff,0xf0,0x00,0x00,0x0f,0xff,0x00,0x00,0x00,0x0f,0xff,0x00,0x00};

static bool comms_code_applied = true;

#if DEBUG_LED_GOAL
static uint8_t debug_features_prev_state = 255;
#endif


static void _soccer_init() {
    ST::soccer.role = ST::soccer.defaultRole;

    OUT::led_O.needsUpdate = true;
    OUT::led_O.color = OUT::LedReduceBrightness(0xFF0040, 1.0f);
    OUT::led_X.needsUpdate = true;
    OUT::led_X.color = OUT::LedReduceBrightness(0xFF0040, 1.0f);
    // OUT::led_Debug.needsUpdate = true;
    // OUT::led_Debug.color[0] = CRGB::Black;
    // OUT::led_Debug.color[1] = CRGB::Black;
    // OUT::led_Debug.color[2] = CRGB::Black;
    // OUT::led_Debug.color[3] = CRGB::Black;
}

static void _drawScreen_SOCCER() {

    OUT::display.needsUpdate = true;
    
    Serial.println("Soccer Mode");

    // display.setTextColor(SSD1306_WHITE);
    // display.setTextWrap(false);
    // display.setTextSize(1);
    display.drawBitmap(50, 11, image_EviSmile1_bits, 36, 42, 1);

    display.setTextSize(1);
    display.setCursor(2, 22);
    if(ST::soccer.role == ST::Types::role_t::Attacker) {
        display.print("A");
    } else if(ST::soccer.role == ST::Types::role_t::Defender) {
        display.print("D");
    } else if(ST::soccer.role == ST::Types::role_t::Test) {
        display.print("T");
    }


}


namespace Mode {
        void soccer() {
            if(ST::state.mode_previous != ST::Types::mode_t::Soccer) { _soccer_init(); _drawScreen_SOCCER();}

            // if(IN::comms.onlineSoccer && IN::comms.rx_soccer_prev_updated == false) {
            //     if(IN::comms.rx_soccer_msg.role != IN::comms.rx_soccer_msg_prev.role) {
            //         if(ST::soccer.role == ST::Types::role_t::Defender) {
            //             ST::soccer.role = ST::Types::role_t::Attacker;
            //         } else if  (ST::soccer.role == ST::Types::role_t::Attacker){
            //             ST::soccer.role = ST::Types::role_t::Defender;
            //         }
            //         _drawScreen_SOCCER();
            //         IN::comms.rx_soccer_prev_updated = true;
            //     }
            // } else {
            //     ST::soccer.role = ST::soccer.defaultRole;
            // }

        

            #if ENABLE_ROLE_CHANGE
                if(IN::comms.onlineSoccer) {
                    if(IN::comms.rx_soccer_msg.code == 1 && comms_code_applied == false) {
                        if(ST::soccer.role == ST::Types::role_t::Defender) { 
                            ST::soccer.role = ST::Types::role_t::Attacker;
                            ST::soccer.attacker.changed_role = true;
                            ST::soccer.attacker.changed_role_time = ST::now_ms;
                        }
                        else if  (ST::soccer.role == ST::Types::role_t::Attacker) { 
                            ST::soccer.role = ST::Types::role_t::Defender;
                            ST::soccer.defender.startedOnLine = false;
                            ST::soccer.defender.attacking = false;
                        }
                        _drawScreen_SOCCER();
                        comms_code_applied = true;
                    } else if (IN::comms.rx_soccer_msg.code == -1 && comms_code_applied == false) {
                        ST::soccer.role = ST::soccer.defaultRole;
                        _drawScreen_SOCCER();
                        comms_code_applied = true;
                    } else if (IN::comms.rx_soccer_msg.code == 0) {
                        comms_code_applied = false;
                    }

                } else {
                    ST::soccer.role = ST::soccer.defaultRole;
                }
            #endif


            if(ST::soccer.role == ST::Types::role_t::Attacker) {
                Role::attacker();
            } else if (ST::soccer.role == ST::Types::role_t::Defender) {
                Role::defender();
            }
            
            if(IN::generic.bukajModuleEn){
                OUT::motorAcc.motEn = true;
            }
    


        #if DEBUG_LED_FEATURES
            uint8_t debug_features_now_state = 0;

            if ((ST::soccer.attacker.lineBounceFeature && ST::soccer.role == ST::Types::role_t::Attacker)||(ST::soccer.defender.lineBounceFeature && ST::soccer.role == ST::Types::role_t::Defender)) {
                debug_features_now_state = 1;   //lineFeature
            } else {
                debug_features_now_state = 0;   // off
            }

            if (debug_features_now_state != debug_features_prev_state) {
                debug_features_prev_state = debug_features_now_state;
                OUT::led_Debug.needsUpdate = true;

                if (debug_features_now_state == 1) {
                    OUT::led_Debug.color[3] = CRGB::White;
                } else {
                    OUT::led_Debug.color[1] = CRGB::Black;
                }
            }
        #endif
    }
}