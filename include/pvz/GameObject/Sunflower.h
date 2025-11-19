#pragma once
#include "pvz/GameObject/Plant.h"
#include "pvz/GameObject/GameObject.hpp"

/**
 * Sunflower - Resource generation plant
 * 
 * Periodically produces sun resources that the player can collect
 * to purchase and plant more plants. Essential for economy management.
 * Inherits plant health and grid management from Plant base class.
 */
class Sunflower : public Plant
{
public:
    Sunflower(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");
        
    void Update() override;  // Generate sun periodically
    
private:
    int sun_clock = randInt(30, 600);  // Countdown timer until next sun (randomized start)
};