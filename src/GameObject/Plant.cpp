#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/Plant.h"
#include "pvz/Framework/PlantManager.h"

Plant::Plant(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : GameObject(imageID, x, y, layer, width, height, animID, name)
{}

// Handle click event - shovel to remove, or just display info
void Plant::OnClick()
{
    if (PlantManager::GetInstance().IsHoldingShovel()) {
        // Remove plant when player is holding shovel
        this->ResetPlantingState();
        PlantManager::GetInstance().SetHoldingShovelState();
        PlantManager::GetInstance().RemovePlantLater(this->GetName());
    }
    else {
        // Just display plant info for debugging
        std::cout << " [" << this->GetName() << "] was clicked.\n";
    }
}

// Reset the planting site state when plant is removed
void Plant::ResetPlantingState()
{
    std::string name = this->GetName();
    std::cout << " [" << name << "] was deleted.\n";
    
    // Remove plant type prefix to get grid coordinates
    // Plant name format: "PlantType" + "row,col"
    size_t pos = name.find(m_plant);
    if (pos != std::string::npos) {
        name.erase(pos, m_plant.length());
    }
    
    // Parse row and column from format "row,col"
    pos = name.find(",");
    if (pos != std::string::npos) {
        int row = std::stoi(name.substr(0, pos));
        int col = std::stoi(name.substr(pos + 1));
        PlantManager::GetInstance().SetPlantingSiteState(row, col, false);
    }
}

// Base update function - override in derived classes for specific behavior
void Plant::Update() 
{
}
