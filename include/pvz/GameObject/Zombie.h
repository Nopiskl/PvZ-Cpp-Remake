#pragma once
#include "pvz/GameObject/GameObject.hpp"
#include <memory>

class PlantingSite;

/**
 * Zombie - Base class for all zombie types
 * 
 * Inherits from GameObject to gain:
 * - Position and sprite rendering system
 * - Animation support for walk/eat states
 * - Layer management for proper rendering order
 * 
 * Provides common zombie AI:
 * - Forward movement (walking left)
 * - Plant detection and collision
 * - Eating behavior when encountering plants
 * - HP system for damage/death
 * 
 * Derived classes (RegularZombie, BucketZombie, PoleVaultZombie)
 * can override Update() for specialized behavior while using
 * BasicUpdate() for standard walk-and-eat AI.
 */
class Zombie : public GameObject
{
public:
    int HP = 0;                  // Zombie health points
    int m_row = -1;              // Which row zombie is in (0-4)
    int m_selfIdx = -1;          // Unique identifier for removal
    std::string m_zombie = "";   // Zombie type identifier
    bool m_isDead = false;       // Death state flag
    bool m_isEating = false;     // Currently eating a plant

    Zombie(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");
   
    // Check if two rectangles overlap (1D collision)
    bool IsColliding(int x1, int width1, int x2, int width2) {
        return x1 < x2 + width2 && x1 + width1 > x2;
    }
    
    // Core zombie AI (can be called by derived classes)
    virtual void BasicUpdate();
    
    // Helper methods for BasicUpdate (separated for clarity)
    bool CheckAndHandlePlantCollision();
    void HandlePlantEating(const std::string& plantName, std::shared_ptr<PlantingSite> site);
    void HandleMovement();
    
    virtual void OnClick() override;
    virtual void Update() override;
};
