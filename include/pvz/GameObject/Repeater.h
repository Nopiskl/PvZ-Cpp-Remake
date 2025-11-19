#pragma once

#include "pvz/GameObject/Plant.h"
#include "pvz/GameObject/GameObject.hpp"

/**
 * Repeater - Advanced offensive plant
 * 
 * Shoots TWO peas in quick succession when zombies are detected,
 * dealing double the damage of a regular Peashooter.
 * Inherits plant health and grid management from Plant base class.
 */
class Repeater : public Plant
{
public:
    Repeater(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");
        
    void Update() override;  // Detect zombies and fire double shot
    
private:
    int m_row = -1;                      // Which row this plant is in
    int m_firstShotTimer = 0;            // Timer for second shot delay
    int m_secondShotTimer = -1;          // Scheduled frame for second shot
    bool m_waitingForZombie = false;     // In cooldown after shooting
};
