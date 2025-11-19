#include "pvz/GameObject/Seed.h"
#include "pvz/Framework/PlantManager.h"
#include "pvz/Framework/StateManager.h"

Seed::Seed(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID, int cooldownTime, int cost,
    const std::string& name)
   : GameObject(imageID, x, y, layer, width, height, animID, name),
     m_isCoolingDown(false), 
     m_cooldownTime(cooldownTime), 
     m_cooldownTimer(cooldownTime),
     cost(cost)
{}

// Handle click event - select this seed for planting
void Seed::OnClick()  {
    auto& plantMgr = PlantManager::GetInstance();
    auto& sunMgr = SunManager::GetInstance();
    auto& stateMgr = StateManager::GetInstance();
    
    // Can't select seed if already holding something
    if (plantMgr.IsHoldingShovel() || plantMgr.IsHoldingUnplantedSeed()) {
        std::cout << "Already holding something" << std::endl;
        return;
    }
    
    // Can't use seed during cooldown
    if (m_isCoolingDown) {
       return;
    }
    
    // Check if player has enough sun
    if (sunMgr.GetSunAmount() < cost) {
        std::cout << "Not enough sun" << std::endl;
        return;
    }

    // Deduct sun cost
    sunMgr.SubtractSunAmount(cost);
    
    // Add cooldown mask overlay
    constexpr int maskWidth = 50;
    constexpr int maskHeight = 70;
    stateMgr.AddMask(
        this->GetName(), 
        std::make_shared<GameObject>(
            ImageID::COOLDOWN_MASK, 
            this->GetX(), 
            this->GetY(), 
            LayerID::COOLDOWN_MASK, 
            maskWidth, 
            maskHeight, 
            AnimID::NO_ANIMATION, 
            this->GetName() + "'s Cover"
        )
    );
    
    // Start cooldown and set player state
    m_isCoolingDown = true;
    plantMgr.SetHoldingPlantState(true);
    plantMgr.HoldingPlant = this->GetName();
}

// Update seed - handle cooldown timer
void Seed::Update() {
    if (m_isCoolingDown) {
        m_cooldownTimer--;
        
        if (m_cooldownTimer <= 0) {
            // Cooldown finished
            m_isCoolingDown = false;
            StateManager::GetInstance().RemoveMask(this->GetName());
            m_cooldownTimer = m_cooldownTime;
        }
    }
}