#pragma once

#include "pvz/GameObject/Plant.h"
#include "pvz/GameObject/GameObject.hpp"

/**
 * Wallnut - Defensive plant
 * 
 * High HP plant used as a barrier to block zombies.
 * Changes appearance (shows cracks) when damaged below 1/3 HP.
 * Inherits plant health and grid management from Plant base class.
 */
class Wallnut : public Plant
{
public:
    Wallnut(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");
        
    void Update() override;  // Update visual state based on HP
    
private:
};