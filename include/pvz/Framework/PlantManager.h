#pragma once
#include "pvz/Framework/PlantFactory.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "pvz/GameObject/Plant.h"
#include "pvz/GameObject/PlantingSite.h"
#include "pvz/Framework/ManagerBase.h"

class Seed;
using PlantSlot = std::pair<std::string, std::shared_ptr<PlantingSite>>;
using PlantGrid = std::vector<std::vector<PlantSlot>>;

// Seed configuration data structure
struct SeedConfig {
    std::string name;
    ImageID seedImageID;
    int xOffset;
    int cooldown;
    int sunCost;
};

class PlantManager : public ManagerBase {
public:
    std::string HoldingPlant;

    std::unordered_map<std::string, std::shared_ptr<Plant>> m_plantLists;
    PlantGrid m_plantingGrid;
    std::unordered_map<std::string, std::shared_ptr<Seed>> m_seedLists;
    
    // Get singleton instance
    static PlantManager& GetInstance();
    
    // Initialize plant manager and register all plants/seeds
    void Init() override;
    
    // Update all plants and seeds each frame
    void Update();
    
    // Add a plant to the game immediately
    void AddPlant(const std::string& type, const std::string& name, int x, int y);
    
    // Remove a plant from the game immediately
    void RemovePlant(const std::string& name);
    
    // Check if player is currently holding the shovel
    bool IsHoldingShovel() const;
    
    // Check if player is currently holding an unplanted seed
    bool IsHoldingUnplantedSeed() const;

    // Schedule a plant to be removed in the next update cycle
    void RemovePlantLater(const std::string& name);
    
    // Schedule a plant to be added in the next update cycle
    void AddPlantLater(const std::string& type, const std::string& name, int x, int y);

    // Set the state of a planting site (occupied or not)
    void SetPlantingSiteState(int row, int col, bool state);

    // Set player's holding plant state
    void SetHoldingPlantState(bool state);
    
    // Toggle shovel holding state
    void SetHoldingShovelState();

    // Clean up all plants and reset state
    void CleanUp() override;

private:
    PlantManager();
    ~PlantManager() = default;
    PlantManager(const PlantManager&) = delete;
    PlantManager& operator=(const PlantManager&) = delete;
    
    // Initialize all seed packets in the UI
    void InitializeSeeds();
    
    // Register all plant types with the factory
    void RegisterPlantFactory();
    
    // Initialize the planting grid
    void InitializePlantingGrid();
    
    // Create and add a seed packet
    void CreateSeedPacket(const SeedConfig& config);
    
    // Add a seed to the seed list
    void AddSeed(const std::string& name, std::shared_ptr<Seed> seed);
    
    // Add a planting site to the grid
    void AddPlantingSite(int row, int col, const std::string& idx, std::shared_ptr<PlantingSite> site);
    
    // Process deferred plant additions
    void ProcessPendingAdditions();
    
    // Process deferred plant deletions
    void ProcessPendingDeletions();
    
    std::vector<std::tuple<std::string, std::string, int, int>> m_plantsToBeAdded;
    std::vector<std::string> m_plantsToBeDeleted;
};
