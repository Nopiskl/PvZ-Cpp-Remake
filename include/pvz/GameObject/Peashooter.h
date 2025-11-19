#pragma once

#include "pvz/GameObject/Plant.h"

/**
 * Peashooter - Basic offensive plant
 * 
 * Shoots peas at zombies when they are detected in the same row.
 * Inherits plant health and grid management from Plant base class.
 */
class Peashooter : public Plant
{
public:
    Peashooter(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");

    void Update() override;      // Check for zombies and shoot
    void ShootPea(int row);      // Fire a pea projectile
    
private:
    int m_shootInterval = 0;     // Cooldown timer between shots
    int m_row;                   // Which row this plant is in
};
