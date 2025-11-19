#include "pvz/GameObject/Pea.h"
#include "pvz/Framework/PeaManager.h"
#include "pvz/Framework/ZombieManager.h"

Pea::Pea(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID, int row, int idx,
    const std::string& name)
    : GameObject(imageID, x, y, layer, width, height, animID, name), 
      m_row(row), 
      m_selfIdx(idx)
{}

// Pea projectile doesn't respond to clicks
void Pea::OnClick() {}

// Update pea projectile - move forward and check for zombie collision
void Pea::Update()
{
    constexpr int peaDamage = 20;
    constexpr int peaSpeed = 8;
    
    if (is_dead) {
        return;
    }

    // Remove pea if it flies off screen
    if (GetX() > WINDOW_WIDTH) {
        is_dead = true;
        return;
    }

    // Build a local cache of zombies in this row for collision detection
    m_rowZombies.clear();
    for (auto& [id, zombie] : ZombieManager::GetInstance().m_zombieLists[m_row]) {
        if (zombie) {
            m_rowZombies[id] = zombie;
        }
    }

    // Find the closest zombie ahead of the pea
    std::shared_ptr<Zombie> closestZombie = nullptr;
    int minDistance = INT_MAX;

    for (auto& [id, zombie] : m_rowZombies) {
        int distance = zombie->GetX() - this->GetX();
        if (distance >= 0 && distance < minDistance) {
            minDistance = distance;
            closestZombie = zombie;
        }
    }

    // Check collision with closest zombie
    if (closestZombie && IsColliding(GetX(), GetWidth(), closestZombie->GetX(), closestZombie->GetWidth())) {
        closestZombie->HP -= peaDamage;
        is_dead = true;  // Pea disappears after hitting
    }
    else {
        // Continue moving forward
        MoveTo(GetX() + peaSpeed, GetY());
    }
}