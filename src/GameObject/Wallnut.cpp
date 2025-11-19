#include "pvz/GameObject/Wallnut.h"
#include "pvz/GameWorld/GameWorld.hpp"

Wallnut::Wallnut(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : Plant(imageID, x, y, layer, width, height, animID, name)
{
    HP = 4000;
    m_plant = "Wallnut";
}

// Update wallnut - change appearance when damaged
void Wallnut::Update()
{
    constexpr int maxHP = 4000;
    constexpr int crackedThreshold = maxHP / 3;  // Show cracked texture at 1/3 HP
    
    // Change to cracked texture when heavily damaged
    if (HP < crackedThreshold) {
        this->ChangeImage(ImageID::WALLNUT_CRACKED);
    }
}

