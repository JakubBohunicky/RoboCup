#include "High/Roles/Primitives/prim_find_goal.h"
#include "High/config_app.h"
#include "High/Services/motion.h"
#include "High/Services/debug.h"

#if DEBUG_LED_GOAL
    bool debug_goal_LED_enabled = false; 
#endif

namespace Prim {

    void find_goal() {


            if(IN::goalEnemy.seen) {
                if(IN::goalEnemy.angle >= -Const::Attacker::shootAngle && IN::goalEnemy.angle <= Const::Attacker::shootAngle) { 
                    OUT::kicker_Drb.kickF = true; 
                }
                Motion::addMotion(IN::goalEnemy.angle, 0.2f);
                Motion::rotate(IN::goalEnemy.angle, ST::pid.slowPIDCfg);
            } else if(ST::soccer.attacker.lineBounceFeature && ST::now_ms - ST::soccer.attacker.lineBounceFeatureTime <= 2000){
                Motion::addMotion_ToNField(180.0f, 0.2f);
                Motion::rotate_ToNField(0.0f, ST::pid.slowPIDCfg); 

            } else {
                if(IN::line.seen && (IN::line.angle > -90.0f && IN::line.angle < 90.0f)) {
                    ST::soccer.attacker.lineBounceFeature = true;
                    ST::soccer.attacker.lineBounceFeatureTime = ST::now_ms;
                } else {
                    Motion::addMotion_ToNField(0.0f, 0.2f);
                    Motion::rotate_ToNField(0.0f, ST::pid.slowPIDCfg); 
                }
            }
            

        // if(IN::motionSens.drbF) {
        //     if(IN::line.seen) {
        //         if(IN::line.angle >= -90 && IN::line.angle <= 90) {
        //             ST::attacker.lineBounceFeature = true;
        //             ST::attacker.lineBounceFeatureTime = ST::now_ms;
        //         }
        //         Motion::addMotion(IN::line.angle + 180, Motion::weight_Soft);
        //     }

        //     if(IN::goalEnemy.seen) {
        //         if(IN::goalEnemy.angle >= -Const::Attacker::shootAngle && IN::goalEnemy.angle <= Const::Attacker::shootAngle) { 
        //             OUT::kicker_Drb.kickF = true; } 
    
        //         Motion::rotate(IN::goalEnemy.angle, ST::pid.slowPIDCfg);
        //     } else {
        //         Motion::rotate_ToNField(0, ST::pid.slowPIDCfg); 

        //         if(ST::attacker.lineBounceFeature == true && IN::line.seen == false) {
        //             Motion::addMotion(180, Motion::weight_Soft);
        //             if(ST::now_ms - ST::attacker.lineBounceFeatureTime >= Const::Attacker::lineBounceFeatureTime_threshold) { ST::attacker.lineBounceFeature = false; }
        //         } else {
        //             if(IN::gyro.offset >= -Const::Attacker::ballAngleNormalSpeed_threshold && IN::gyro.offset <= Const::Attacker::ballAngleNormalSpeed_threshold) { Motion::addMotion_ToNField(0, Motion::weight_Normal); }
        //             else { Motion::addMotion_ToNField(0, Motion::weight_Soft); }
        //         }
        //     } 
        // }
        // else if(IN::motionSens.drbR) { } 



        #if DEBUG_LED_GOAL
            if(debug_goal_LED_enabled != IN::goalEnemy.seen) {
                debug_goal_LED_enabled = IN::goalEnemy.seen;
                OUT::led_Debug.needsUpdate = true;
                if(IN::goalEnemy.seen == true) {
                    OUT::led_Debug.color[1] = CRGB::DarkMagenta;
            } 
            } else  if(debug_goal_LED_enabled != ST::soccer.attacker.lineBounceFeature) {
                debug_goal_LED_enabled = ST::soccer.attacker.lineBounceFeature;
                OUT::led_Debug.needsUpdate = true;
                if(ST::soccer.attacker.lineBounceFeature == true) {
                    OUT::led_Debug.color[1] = CRGB::White;
                }
            } else if(debug_goal_LED_enabled != IN::goalOur.seen) {
                debug_goal_LED_enabled = IN::goalOur.seen;
                OUT::led_Debug.needsUpdate = true;
                if(IN::goalOur.seen == true) {
                    OUT::led_Debug.color[1] = CRGB::DarkGreen;
                }
            } else {
                    OUT::led_Debug.color[1] = CRGB::Black;
                }
        #endif
            

    }



        void defender_find_our_goal() {


            if(IN::goalOur.seen) {
                Motion::addMotion(IN::goalOur.angle, 0.2f);
                Motion::rotate(IN::goalOur.angle, ST::pid.slowPIDCfg);
            } else if(ST::soccer.defender.lineBounceFeature && ST::now_ms - ST::soccer.defender.lineBounceFeatureTime <= 2000){
                Motion::addMotion_ToNField(0.0f, 0.2f);
                Motion::rotate_ToNField(180.0f, ST::pid.normalPIDCfg); 

            } else {
                // if(IN::line.seen && (IN::line.angle > -90.0f && IN::line.angle < 90.0f)) {
                if(IN::line.seen){
                    ST::soccer.defender.lineBounceFeature = true;
                    ST::soccer.defender.lineBounceFeatureTime = ST::now_ms;
                } else {
                    Motion::addMotion_ToNField(180.0f, 0.2f);
                    Motion::rotate_ToNField(180.0f, ST::pid.slowPIDCfg); 
                }
            }
            




        #if DEBUG_LED_GOAL
            if(debug_goal_LED_enabled != IN::goalEnemy.seen) {
                debug_goal_LED_enabled = IN::goalEnemy.seen;
                OUT::led_Debug.needsUpdate = true;
                if(IN::goalEnemy.seen == true) {
                    OUT::led_Debug.color[1] = CRGB::DarkMagenta;
            } 
            } else  if(debug_goal_LED_enabled != ST::soccer.defender.lineBounceFeature) {
                debug_goal_LED_enabled = ST::soccer.defender.lineBounceFeature;
                OUT::led_Debug.needsUpdate = true;
                if(ST::soccer.defender.lineBounceFeature == true) {
                    OUT::led_Debug.color[1] = CRGB::White;
                }
            } else if(debug_goal_LED_enabled != IN::goalOur.seen) {
                debug_goal_LED_enabled = IN::goalOur.seen;
                OUT::led_Debug.needsUpdate = true;
                if(IN::goalOur.seen == true) {
                    OUT::led_Debug.color[1] = CRGB::DarkGreen;
                }
            } else {
                    OUT::led_Debug.color[1] = CRGB::Black;
                }
        #endif
            

    }



}