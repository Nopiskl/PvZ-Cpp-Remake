#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "pvz/Framework/ManagerBase.h"
#include "pvz/GameObject/Pea.h"

class PeaManager : public ManagerBase {
public:
    static int pea_idx;
    static PeaManager& GetInstance();
    void Init() override;
    void Update();
    void AddPea(int x, int y, int row);
    void RemovePea(int idx);
    void CleanUp() override;

    std::vector<int> pea_to_be_removed;

    std::unordered_map <int, std::shared_ptr<Pea>> pea_lists;
private:
    PeaManager() = default;
    ~PeaManager() = default;
    PeaManager(const PeaManager&) = delete;
    PeaManager& operator=(const PeaManager&) = delete;


};