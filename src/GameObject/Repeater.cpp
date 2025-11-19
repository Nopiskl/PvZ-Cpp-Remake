#include "pvz/GameObject/Repeater.h"
#include "pvz/GameWorld/GameWorld.hpp"

Repeater::Repeater(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : Plant(imageID, x, y, layer, width, height, animID, name), 
      m_row(y / LAWN_GRID_HEIGHT)
{
    HP = 300;
    m_plant = "Repeater";
}

// Update repeater - shoots two peas in quick succession when zombie detected
void Repeater::Update()
{
    constexpr int peaOffsetX = 30;
    constexpr int peaOffsetY = 20;
    constexpr int secondShotDelay = 5;   // Frames between first and second shot
    constexpr int cooldownFrames = 30;   // Total cooldown period
    
    // Check for zombies in the same row
    const auto& zombiesInRow = ZombieManager::GetInstance().m_zombieLists[m_row];
    bool zombieInFront = false;

    for (const auto& [id, zombie] : zombiesInRow) {
        if (zombie && zombie->GetX() > this->GetX()) {
            zombieInFront = true;
            break;
        }
    }

    // Start shooting sequence when zombie is detected
    if (!m_waitingForZombie && zombieInFront) {
        // Fire first pea
        PeaManager::GetInstance().AddPea(
            this->GetX() + peaOffsetX, 
            this->GetY() + peaOffsetY, 
            m_row
        );
        m_waitingForZombie = true;
        m_firstShotTimer = 0;
        m_secondShotTimer = secondShotDelay;
        return;
    }

    // Handle second shot and cooldown
    if (m_waitingForZombie) {
        m_firstShotTimer++;

        // Fire second pea after short delay
        if (m_firstShotTimer == m_secondShotTimer) {
            PeaManager::GetInstance().AddPea(
                this->GetX() + peaOffsetX, 
                this->GetY() + peaOffsetY, 
                m_row
            );
        }

        // Reset after cooldown period
        if (m_firstShotTimer >= cooldownFrames) {
            m_waitingForZombie = false;
            m_firstShotTimer = 0;
            m_secondShotTimer = -1;
        }
    }
}


