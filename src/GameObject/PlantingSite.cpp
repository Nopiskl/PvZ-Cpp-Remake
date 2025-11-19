#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/PlantingSite.h"
#include "pvz/Framework/PlantManager.h"

PlantingSite::PlantingSite(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : GameObject(imageID, x, y, layer, width, height, animID, name)
{}

// Handle click event - plant a seed if player is holding one
void PlantingSite::OnClick()
{
    std::cout << " [" << this->GetName() << "] was clicked.\n";

    auto& plantMgr = PlantManager::GetInstance();
    
    // Check if player is holding a seed to plant
    if (!plantMgr.IsHoldingUnplantedSeed()) {
        return;
    }
    
    // Don't allow planting on occupied sites
    if (has_plant) {
        return;
    }
    
    std::string holdingPlant = plantMgr.HoldingPlant;
    std::string objectName = holdingPlant + this->GetName();

    // Update grid state
    plantMgr.m_plantingGrid[m_row][m_col].first = holdingPlant;
    
    // Create the plant at this location
    plantMgr.AddPlantLater(holdingPlant, objectName, this->GetX(), this->GetY());
    
    // Reset player state
    plantMgr.SetHoldingPlantState(false);
    has_plant = true;
}

// Set whether this site has a plant on it
void PlantingSite::SetSiteState(bool state)
{
    has_plant = state;
}


