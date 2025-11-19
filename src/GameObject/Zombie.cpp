#include "pvz/GameObject/Zombie.h"
#include "pvz/Framework/ZombieManager.h"
#include "pvz/Framework/PlantManager.h"

Zombie::Zombie(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : GameObject(imageID, x, y, layer, width, height, animID, name), 
      m_row(y / LAWN_GRID_HEIGHT)
{}

// Main update function called each frame
void Zombie::Update()
{
    BasicUpdate();
}

// Basic zombie behavior: check health, handle collisions, and move
void Zombie::BasicUpdate()
{
    // Check if zombie should die
    if (HP <= 0) {
        m_isDead = true;
    }
    
    if (m_isDead) {
        ZombieManager::GetInstance().RemoveZombieLater(m_selfIdx);
        return;
    }

    // Check for plant collision and handle eating
    bool collidedWithPlant = CheckAndHandlePlantCollision();
    
    // If not eating, continue moving forward
    if (!collidedWithPlant) {
        HandleMovement();
    }
}

// Check for collision with plants and handle eating behavior
bool Zombie::CheckAndHandlePlantCollision()
{
    auto& row = PlantManager::GetInstance().m_plantingGrid[m_row];
    
    for (auto& [name, site] : row) {
        if (!site || !site->GetPlantSite()) {
            continue;
        }

        int plantX = site->GetX();
        int plantW = site->GetWidth();
        int zombieX = this->GetX();
        int zombieW = this->GetWidth();

        if (IsColliding(zombieX, zombieW, plantX, plantW)) {
            HandlePlantEating(name, site);
            return true;
        }
    }
    return false;
}

// Handle eating a plant at the current location
void Zombie::HandlePlantEating(const std::string& plantName, std::shared_ptr<PlantingSite> site)
{
    // Start eating animation if not already eating
    if (!m_isEating) {
        m_isEating = true;
        this->PlayAnimation(AnimID::EAT);
    }

    // Find and damage the plant
    auto& plantLists = PlantManager::GetInstance().m_plantLists;
    std::string fullPlantName = plantName + site->GetName();

    auto it = plantLists.find(fullPlantName);
    if (it != plantLists.end()) {
        auto& plant = it->second;
        plant->HP -= 3;
        
        // Remove plant when health depletes
        if (plant->HP <= 0) {
            plant->ResetPlantingState();
            PlantManager::GetInstance().RemovePlantLater(fullPlantName);
            m_isEating = false;
            this->PlayAnimation(AnimID::WALK);
        }
    }
}

// Handle zombie forward movement
void Zombie::HandleMovement()
{
    // Resume walking if was eating
    if (m_isEating) {
        this->PlayAnimation(AnimID::WALK);
        m_isEating = false;
    }
    
    // Move forward (to the left)
    this->MoveTo(this->GetX() - 1, this->GetY());
}

// Handle click event - debug feature disabled in production
void Zombie::OnClick() 
{
	// Debug feature: click to remove zombie (disabled for normal gameplay)
	// ZombieManager::GetInstance().RemoveZombieLater(m_selfIdx);
}