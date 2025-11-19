#pragma once

#include "pvz/GameObject/GameObject.hpp"

/**
 * Plant - Base class for all plant types
 * 
 * Inherits from GameObject to gain:
 * - Position and size management (x, y, width, height)
 * - Sprite rendering (imageID, animID)
 * - Layer ordering for proper z-order rendering
 * 
 * Provides common plant functionality:
 * - HP system for plant health
 * - Click handling for shovel removal
 * - Grid position management
 */
class Plant : public GameObject
{
public:
    int HP = 0;                  // Plant health points
    std::string m_plant = "";    // Plant type identifier
    bool is_dead = false;        // Death state flag

    Plant(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID, 
        const std::string& name = "");

    virtual void OnClick() override;
    virtual void Update() override;
    
    // Reset the grid cell state when plant is removed
    void ResetPlantingState();
};