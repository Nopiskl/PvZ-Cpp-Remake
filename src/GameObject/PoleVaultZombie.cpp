#include "pvz/GameObject/PoleVaultZombie.h"
#include "pvz/GameObject/Zombie.h"
#include "pvz/Framework/ZombieManager.h"
#include "pvz/Framework/PlantManager.h"

PoleVaultZombie::PoleVaultZombie(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : Zombie(imageID, x, y, layer, width, height, animID, name)
{
    HP = 340;
    m_zombie = "PoleVaultZombie";
}

void PoleVaultZombie::Update() {
    if (HP <= 0) {
        m_isDead = true;
    }

    if (m_isDead) {
        ZombieManager::GetInstance().RemoveZombieLater(m_selfIdx);
        return;
    }

    if (m_isJumping) {
        m_jumpAnimTicks++;
        if (m_jumpAnimTicks >= 42) {
            m_isJumping = false;
            m_hasJumped = true;
            this->PlayAnimation(AnimID::WALK);
            this->MoveTo(GetX() - 150, GetY());
        }
        return;
    }

    bool collidedWithPlant = false;
    auto& row = PlantManager::GetInstance().m_plantingGrid[m_row];

    if (!m_hasJumped) {
        this->MoveTo(GetX() - 40, GetY());

        for (auto& [name, site] : row) {
            if (!site || !site->GetPlantSite()) {
                continue;
            }

            int plantX = site->GetX();
            int plantW = site->GetWidth();
            int zombieX = GetX();
            int zombieW = GetWidth();

            if (IsColliding(zombieX, zombieW, plantX, plantW)) {
                m_isJumping = true;
                m_jumpAnimTicks = 0;
                this->PlayAnimation(AnimID::JUMP);
                this->MoveTo(GetX() + 40, GetY());
                return;
            }
        }

        this->MoveTo(GetX() + 40, GetY());
    }

    for (auto& [name, site] : row) {
        if (!site || !site->GetPlantSite()) {
            continue;
        }

        int plantX = site->GetX();
        int plantW = site->GetWidth();
        int zombieX = GetX();
        int zombieW = GetWidth();

        if (IsColliding(zombieX, zombieW, plantX, plantW)) {
            if (!m_isEating) {
                m_isEating = true;
                this->PlayAnimation(AnimID::EAT);
            }

            auto& plantLists = PlantManager::GetInstance().m_plantLists;
            auto it = plantLists.find(name + site->GetName());

            if (it != plantLists.end()) {
                auto& plant = it->second;
                plant->HP -= 3;
                if (plant->HP <= 0) {
                    plant->ResetPlantingState();
                    PlantManager::GetInstance().RemovePlantLater(name + site->GetName());
                    m_isEating = false;
                    this->PlayAnimation(AnimID::WALK);
                }
            }

            collidedWithPlant = true;
            break;
        }
    }

    if (!collidedWithPlant && !m_isJumping) {
        m_isEating = false;
        if (!m_hasJumped) {
            this->MoveTo(GetX() - 2, GetY());
        }
        else {
            this->MoveTo(GetX() - 1, GetY());
        }
    }
}
