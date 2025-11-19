#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "pvz/Framework/ManagerBase.h"
#include "pvz/GameObject/Zombie.h"
#include "pvz/Framework/ZombieFactory.h"

class ZombieManager : public ManagerBase {
public:
    static int s_zombieIdx;
    
    // Get singleton instance
    static ZombieManager& GetInstance();
    
    // Initialize zombie manager and register all zombie types
    void Init() override;
    
    // Update all zombies each frame
    void Update();
    
    // Clean up all zombies and reset state
    void CleanUp();
    
    // Add a zombie to the game immediately
    void AddZombie(const std::string& type, const std::string& name, int x, int y, int row);
    
    // Remove a zombie from the game immediately
    void RemoveZombie(int idx);
    
    // Schedule a zombie to be added in the next update cycle
    void AddZombieLater(const std::string& type, const std::string& name, int x, int y, int row);
    
    // Schedule a zombie to be removed in the next update cycle
    void RemoveZombieLater(int idx);
    
    // Check if any zombie has reached the left boundary (game over condition)
    bool HasZombieOutOfLeftBound();
    
    std::vector<std::unordered_map<int, std::shared_ptr<Zombie>>> m_zombieLists =
        std::vector<std::unordered_map<int, std::shared_ptr<Zombie>>>(GAME_ROWS);

private:
    ZombieManager() = default;
    ~ZombieManager() = default;
    ZombieManager(const ZombieManager&) = delete;
    ZombieManager& operator=(const ZombieManager&) = delete;
    
    // Register all zombie types with the factory
    void RegisterZombieFactory();
    
    // Process deferred zombie additions
    void ProcessPendingAdditions();
    
    // Process deferred zombie deletions
    void ProcessPendingDeletions();
    
    std::vector<std::tuple<std::string, std::string, int, int, int>> m_zombiesToBeAdded;
    std::vector<int> m_zombiesToBeDeleted;
};