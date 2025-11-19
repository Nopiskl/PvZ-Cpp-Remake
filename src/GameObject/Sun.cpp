#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/Sun.h"
#include "pvz/Framework/SunManager.h"

int Sun::s_idx = 0;

Sun::Sun(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID, bool is_sunflower,
    const std::string& name)
    : GameObject(imageID, x, y, layer, width, height, animID, name), 
      is_sun_flower(is_sunflower)
{
    m_selfIdx = s_idx++;
}

// Handle click event - collect sun and add to player's resources
void Sun::OnClick() {
    constexpr int sunValue = 25;  // Sun resource value
    
    SunManager::GetInstance().AddSunAmount(sunValue);
    SunManager::GetInstance().RemoveSun(this->m_selfIdx);
}