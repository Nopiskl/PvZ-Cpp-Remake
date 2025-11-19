#pragma once

#include "pvz/GameObject/Zombie.h"

/**
 * BucketZombie - Armored zombie variant
 * 
 * Same behavior as RegularZombie but with much higher HP (1300 vs 200)
 * due to bucket armor. Uses the base Zombie class's walk-and-eat AI.
 * Inherits all zombie behavior from Zombie base class.
 */
class BucketZombie : public Zombie
{
public:
    BucketZombie(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");

    void Update() override;  // Uses BasicUpdate, just tankier

private:
};