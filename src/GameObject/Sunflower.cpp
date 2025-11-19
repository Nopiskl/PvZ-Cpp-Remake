#include "pvz/GameObject/Plant.h"
#include "pvz/GameObject/Sunflower.h"
#include "pvz/GameWorld/GameWorld.hpp"

Sunflower::Sunflower(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : Plant(imageID, x, y, layer, width, height, animID, name)
{
    HP = 200;
    m_plant = "Sunflower";
}

// Update sunflower - periodically produces sun resources
void Sunflower::Update()
{
    constexpr int sunProductionInterval = 600;  // Frames between sun generation (~20 seconds)
    constexpr int sunWidth = 80;
    constexpr int sunHeight = 80;
    
    if (sun_clock <= 0) {
        // Generate a new sun at sunflower's position
        SunManager::GetInstance().AddSun(
            std::make_shared<Sun>(
                ImageID::SUN, 
                this->GetX(), 
                this->GetY(), 
                LayerID::SUN, 
                sunWidth, 
                sunHeight, 
                AnimID::IDLE, 
                true,  // Produced by sunflower
                "FlowerSun"
            )
        );
        sun_clock = sunProductionInterval;
    }
    else {
        sun_clock--;
    }
}

