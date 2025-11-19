#include "pvz/Framework/StateManager.h"
#include "pvz/GameObject/Shovel.h"
#include "pvz/Framework/SunManager.h"
#include "pvz/Framework/PlantManager.h"
#include "pvz/GameObject/Seed.h"

StateManager& StateManager::GetInstance() {
    static StateManager instance;
    return instance;
}

void StateManager::Update()
{
	ExploseUpdate(); 

	// Update seed packet masks based on sun availability
	for (const auto& [name, seed] : PlantManager::GetInstance().m_seedLists)
	{
		if (SunManager::GetInstance().GetSunAmount() < seed->cost)
		{
			StateManager::GetInstance().AddMask(seed->GetName() + "Sun", 
				std::make_shared<GameObject>(ImageID::COOLDOWN_MASK, seed->GetX(), seed->GetY(), 
					LayerID::COOLDOWN_MASK, 50, 70, AnimID::NO_ANIMATION, seed->GetName() + "\'s Mask"));
		}
		else 
		{
			StateManager::GetInstance().RemoveMask(seed->GetName() + "Sun");
		}
	}
}

void StateManager::Init()
{
	StateManager::shovel = std::make_shared<Shovel>(ImageID::SHOVEL, 600, WINDOW_HEIGHT - 40, LayerID::UI, 50, 50, AnimID::NO_ANIMATION, "Shovel");
}

void StateManager::AddMask(std::string name, std::shared_ptr<GameObject> obj) {
	cooldownmask_lists[name] = obj;
}

void StateManager::RemoveMask(std::string name)
{
	cooldownmask_lists.erase(name);
}

void StateManager::Explose(int x,int y)
{
	explosion_lists[explosion_idx] = std::make_shared<Explosion>(ImageID::EXPLOSION, x, y, LayerID::PROJECTILES, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, AnimID::NO_ANIMATION, "Explosion");
	explosion_idx++;
}

void StateManager::ExploseUpdate()
{
	int idx = -1;
	for (auto it : explosion_lists)
	{
		if (it.second->cnt >= 3) {
			idx = it.first;
		}
		else it.second->cnt++;
	}
	explosion_lists.erase(idx);
}

void StateManager::CleanUp() {
	explosion_lists.clear();

	cooldownmask_lists.clear();

	explosion_idx = 0;

	shovel.reset();

	Mouse_state = {};  

}

