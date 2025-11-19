#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__


#include <list>
#include <memory>
#include "pvz/GameObject/Seed.h"
#include "pvz/GameObject/Sun.h"
#include "pvz/Framework/SunManager.h"
#include "pvz/Framework/WaveManager.h"
#include "pvz/Framework/PlantManager.h"
#include "pvz/Framework/StateManager.h"
#include "pvz/GameObject/Zombie.h"
#include "pvz/Framework/ZombieManager.h"
#include "pvz/Framework/ZombieFactory.h"
#include "pvz/GameObject/Plant.h"
#include "pvz/GameObject/Wallnut.h"
#include "pvz/GameObject/Peashooter.h"
#include "pvz/GameObject/CherryBomb.h"
#include "pvz/GameObject/Repeater.h"
#include "pvz/GameObject/Sunflower.h"
#include "pvz/GameObject/Shovel.h"
#include "pvz/GameObject/PlantingSite.h"
#include "pvz/GameObject/RegularZombie.h"
#include "pvz/Framework/WorldBase.hpp"
#include <unordered_map>
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/Framework/PlantFactory.h"
#include "pvz/Framework/TextBase.hpp"
#include "pvz/utils.hpp"
#include "pvz/Framework/PeaManager.h"


// Consider:
// Use shared_from_this() instead of "this" to create a pointer to oneself?
// Use unique_ptr<> / shared_ptr<> to manage GameObjects?

class GameWorld : public WorldBase {
public:
  GameWorld() = default;
  ~GameWorld() = default;
  void Init() override;
  LevelStatus Update() override;
  void CleanUp() override;

private:
	void ShowWaves();
	void InitBackgroundResources();
	std::shared_ptr<Background> background;

};

#endif // !GAMEWORLD_HPP__
