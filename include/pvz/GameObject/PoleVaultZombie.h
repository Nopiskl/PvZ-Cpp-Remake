#pragma once

#include "pvz/GameObject/Zombie.h"

/**
 * PoleVaultZombie - Special ability zombie
 * 
 * Can jump over the first plant it encounters using a pole vault.
 * After jumping, behaves like a regular zombie. Only jumps once.
 * This class demonstrates behavior specialization through inheritance.
 */
class PoleVaultZombie : public Zombie
{
public:
    PoleVaultZombie(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");

    void Update() override;  // Custom AI for jumping over first plant

private:
    bool m_hasJumped = false;    // Whether zombie has used its jump ability
    bool m_isJumping = false;    // Currently in jump animation
    int m_jumpAnimTicks = 0;     // Jump animation frame counter
};