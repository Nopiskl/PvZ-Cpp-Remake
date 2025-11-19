#pragma once

#include "pvz/GameObject/Plant.h"
#include "pvz/GameObject/GameObject.hpp"

/**
 * CherryBomb - Explosive instant-use plant
 * 
 * Explodes after a short delay, dealing massive damage to all
 * zombies in a 3x3 area. Self-destructs after explosion.
 * Inherits plant health and grid management from Plant base class.
 */
class CherryBomb : public Plant
{
public:
    CherryBomb(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");

    void Update() override;  // Count down to explosion
    
    // Check collision between two rectangles (1D overlap test)
    bool IsColliding(int x1, int width1, int x2, int width2) {
        return x1 < x2 + width2 && x1 + width1 > x2;
    }

private:
    // Handle explosion and damage all zombies in range
    void ExplodeAndDamageZombies();
    
    int m_timer = 0;      // Countdown to explosion
    int m_interval = 0;   // Frame when explosion should trigger
};
