#include "pvz/GameObject/Peashooter.h"
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/Framework/PeaManager.h"

Peashooter::Peashooter(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : Plant(imageID, x, y, layer, width, height, animID, name), 
      m_row(y / LAWN_GRID_HEIGHT)
{
    HP = 300;
    m_plant = "Peashooter";
}

// Update peashooter - shoot peas at zombies in the same row
void Peashooter::Update()
{
    constexpr int shootCooldown = 30;  // Frames between shots
    m_shootInterval++;

    // Check if cooldown has elapsed
    if (m_shootInterval < shootCooldown) {
        return;
    }

    // Check for zombies in the same row
    const auto& zombiesInRow = ZombieManager::GetInstance().m_zombieLists[m_row];
    for (const auto& [id, zombie] : zombiesInRow) {
        if (!zombie) {
            continue;
        }

        // Shoot if zombie is ahead (to the right)
        if (zombie->GetX() > this->GetX()) {
            ShootPea(m_row);
            m_shootInterval = 0;
            break;
        }
    }
}

// Shoot a pea projectile
void Peashooter::ShootPea(int row)
{
    constexpr int peaOffsetX = 30;  // Pea spawn offset from plant center
    constexpr int peaOffsetY = 20;
    
    PeaManager::GetInstance().AddPea(
        this->GetX() + peaOffsetX, 
        this->GetY() + peaOffsetY, 
        row
    );
}