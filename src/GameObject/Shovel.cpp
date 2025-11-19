#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/Shovel.h"
#include "pvz/Framework/PlantManager.h"

Shovel::Shovel(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : GameObject(imageID, x, y, layer, width, height, animID, name)
{}

// Handle click event - toggle shovel tool for removing plants
void Shovel::OnClick()
{
    PlantManager::GetInstance().SetHoldingShovelState();
    std::cout << " [" << this->GetName() << "] was clicked.\n";
}
