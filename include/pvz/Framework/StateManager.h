#pragma once
#include <unordered_map>
#include <memory>
#include "pvz/utils.hpp"
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/Framework/ManagerBase.h"
#include "pvz/GameObject/Explosion.h"

class Shovel;

struct Mouse_state {
    bool IsHoldingShovel = false;
    bool IsHoldingUnplantedSeed = false;
};

class StateManager : public ManagerBase {
public:
    int explosion_idx = 0;
    static StateManager& GetInstance();
    void Update();
    void Init() override;
    Mouse_state Mouse_state;
    void ExploseUpdate();
    void SetPlantingSiteState(std::string name, bool state);
    void AddMask(std::string name, std::shared_ptr<GameObject> obj);
    void RemoveMask(std::string name);
    void Explose(int x,int y);
    void CleanUp() override;
private:
    StateManager() = default;
    ~StateManager() = default;
    StateManager(const StateManager&) = delete;
    StateManager& operator=(const StateManager&) = delete;
    std::shared_ptr<Shovel> shovel;
    std::unordered_map <int,std::shared_ptr<Explosion>> explosion_lists;
    std::unordered_map <std::string, std::shared_ptr<GameObject>> cooldownmask_lists;
};
