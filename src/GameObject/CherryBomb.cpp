#include "pvz/GameObject/CherryBomb.h"
#include "pvz/GameWorld/GameWorld.hpp"

CherryBomb::CherryBomb(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : Plant(imageID, x, y, layer, width, height, animID, name)
{
    HP = 4000; 
    m_plant = "CherryBomb";
}

// Update cherry bomb - explode after delay and damage all nearby zombies
void CherryBomb::Update()
{
    if (is_dead) {
        return;
    }

    constexpr int explosionDelay = 15;  // Frames before explosion
    
    if (m_interval >= explosionDelay) {
        ExplodeAndDamageZombies();
    }
    else {
        m_interval++;
    }
}

// Explode and deal massive damage to all zombies in range
void CherryBomb::ExplodeAndDamageZombies()
{
    constexpr int explosionDamage = 2000;
    constexpr double explosionRangeMultiplier = 1.5;
    
    int centerX = this->GetX();
    int centerY = this->GetY();

    // Calculate explosion range (1.5 grid cells in each direction)
    int rangeHalfWidth = LAWN_GRID_WIDTH * explosionRangeMultiplier;
    int rangeHalfHeight = LAWN_GRID_HEIGHT * explosionRangeMultiplier;

    int rangeLeft = centerX - rangeHalfWidth;
    int rangeRight = centerX + rangeHalfWidth;
    int rangeTop = centerY - rangeHalfHeight;
    int rangeBottom = centerY + rangeHalfHeight;

    // Damage all zombies within explosion range
    for (int row = 0; row < GAME_ROWS; ++row) {
        for (auto& [id, zombie] : ZombieManager::GetInstance().m_zombieLists[row]) {
            if (!zombie) {
                continue;
            }

            int zx = zombie->GetX();
            int zy = zombie->GetY();
            int zw = zombie->GetWidth();
            int zh = zombie->GetHeight();

            // Check if zombie is within explosion range
            if (IsColliding(rangeLeft, rangeRight - rangeLeft, zx, zw) &&
                IsColliding(rangeTop, rangeBottom - rangeTop, zy, zh)) {
                zombie->HP -= explosionDamage;
            }
        }
    }
    
    // Remove cherry bomb after explosion
    is_dead = true;
    ResetPlantingState();
    StateManager::GetInstance().Explose(GetX(), GetY());
    PlantManager::GetInstance().RemovePlantLater(GetName());
}


