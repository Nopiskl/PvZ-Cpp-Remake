#include "pvz/FrameWork/PeaManager.h"


int PeaManager::pea_idx = 0;

PeaManager& PeaManager::GetInstance() {
	static PeaManager instance;
	return instance;
}

void PeaManager::Init()
{}

void PeaManager::Update()
{
    for (auto& [id, pea_ptr] : pea_lists) {
        if (pea_ptr && !pea_ptr->is_dead) {
            pea_ptr->Update();
        }
    }

    std::vector<int> to_remove;
    for (auto& [id, pea_ptr] : pea_lists) {
        if (pea_ptr && pea_ptr->is_dead) {
            to_remove.push_back(id);
        }
    }

    for (int id : to_remove) {
        RemovePea(id);
    }
}

void PeaManager::AddPea(int x, int y, int row)
{
	pea_lists[pea_idx] = std::make_shared<Pea>(ImageID::PEA, x, y, LayerID::PROJECTILES, 28, 28, AnimID::NO_ANIMATION ,row ,pea_idx,"Pea");
	pea_idx++;
}

void PeaManager::RemovePea(int idx)
{
	pea_lists.erase(idx);
}

void PeaManager::CleanUp() {
    pea_lists.clear();              
    pea_to_be_removed.clear();     
    pea_idx = 0;                    
}