#include "pvz/GameWorld/GameWorld.hpp"


void GameWorld::Init() {
	InitBackgroundResources();
	SunManager::GetInstance().Init();
	WaveManager::GetInstance().Init();
	PlantManager::GetInstance().Init();
	StateManager::GetInstance().Init();
	ZombieManager::GetInstance().Init();
	PeaManager::GetInstance().Init();
}

void GameWorld::InitBackgroundResources()
{
	GameWorld::background = std::make_shared<Background>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

LevelStatus GameWorld::Update() {

	SunManager::GetInstance().Update();
	WaveManager::GetInstance().Update();
	PlantManager::GetInstance().Update();
	StateManager::GetInstance().Update();
	ZombieManager::GetInstance().Update();
	PeaManager::GetInstance().Update();


	if (ZombieManager::GetInstance().HasZombieOutOfLeftBound())	return LevelStatus::LOSING;
	else return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
	SunManager::GetInstance().CleanUp();
	WaveManager::GetInstance().CleanUp();
	PlantManager::GetInstance().CleanUp();
	StateManager::GetInstance().CleanUp();
	ZombieManager::GetInstance().CleanUp();
	PeaManager::GetInstance().CleanUp();
}
