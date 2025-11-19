#pragma once

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/GameObject/Zombie.h"

/**
 * RegularZombie - Basic zombie type
 * 
 * Standard zombie with low HP and no special abilities.
 * Uses the base Zombie class's walk-and-eat AI (BasicUpdate).
 * Inherits all zombie behavior from Zombie base class.
 */
class RegularZombie : public Zombie
{
public:
    RegularZombie(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");

    void Update() override;  // Uses BasicUpdate for standard behavior

private:
};