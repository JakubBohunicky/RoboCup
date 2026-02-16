#pragma once
#include <cstdint>

namespace WORLDRAW{

    struct Goal {

        bool seen = false;
        float angle = 0.0f; //Angle from -180 to 180
        uint16_t size = 0;
    };

    struct Ball
    {

        int16_t angle = 0; 
        uint16_t distRaw = 0;
        float strenght = 0.0f; //from 1-closest to 0-furthest 
        
    };

} // namespace WorldRaw



struct  WorldIn{
    
    WORLDRAW::Goal goalEnemy;
    WORLDRAW::Goal goalOur;
    WORLDRAW::Ball ball;
};
