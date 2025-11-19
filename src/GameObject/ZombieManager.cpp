#include "pvz/Framework/ZombieManager.h"
#include "pvz/GameObject/RegularZombie.h"
#include "pvz/Framework/ZombieFactory.h"
#include "pvz/GameObject/PoleVaultZombie.h"
#include "pvz/GameObject/BucketZombie.h"

int ZombieManager::s_zombieIdx = 0;

ZombieManager& ZombieManager::GetInstance() {
	static ZombieManager instance;
	return instance;
}

void ZombieManager::Init()
{
	RegisterZombieFactory();
}

void ZombieManager::RegisterZombieFactory()
{
	// Common zombie properties
	constexpr int zombieWidth = 20;
	constexpr int zombieHeight = 80;
	constexpr LayerID zombieLayer = LayerID::ZOMBIES;

	// Register all zombie types with their factory creators
	ZombieFactory::Register("RegularZombie", [=](int x, int y, const std::string& name) {
		return std::make_shared<RegularZombie>(
			ImageID::REGULAR_ZOMBIE, x, y, zombieLayer, 
			zombieWidth, zombieHeight, AnimID::WALK, name
		);
	});
	
	ZombieFactory::Register("BucketZombie", [=](int x, int y, const std::string& name) {
		return std::make_shared<BucketZombie>(
			ImageID::BUCKET_HEAD_ZOMBIE, x, y, zombieLayer, 
			zombieWidth, zombieHeight, AnimID::WALK, name
		);
	});
	
	ZombieFactory::Register("PoleVaultZombie", [=](int x, int y, const std::string& name) {
		return std::make_shared<PoleVaultZombie>(
			ImageID::POLE_VAULTING_ZOMBIE, x, y, zombieLayer, 
			zombieWidth, zombieHeight, AnimID::RUN, name
		);
	});
}

void ZombieManager::Update()
{
	// Update all zombies in each row
	for (int row = 0; row < GAME_ROWS; row++) {
		for (auto& [id, zombie] : m_zombieLists[row]) {
			if (zombie) {
				zombie->Update();
			}
		}
	}

	// Process deferred operations to avoid iterator invalidation
	ProcessPendingDeletions();
	ProcessPendingAdditions();
}

void ZombieManager::ProcessPendingDeletions()
{
	for (int id : m_zombiesToBeDeleted) {
		RemoveZombie(id);
	}
	m_zombiesToBeDeleted.clear();
}

void ZombieManager::ProcessPendingAdditions()
{
	for (const auto& [type, name, x, y, row] : m_zombiesToBeAdded) {
		AddZombie(type, name, x, y, row);
	}
	m_zombiesToBeAdded.clear();
}

void ZombieManager::AddZombieLater(const std::string& type, const std::string& name, int x, int y, int row) {
	m_zombiesToBeAdded.emplace_back(type, name, x, y, row);
}

void ZombieManager::RemoveZombieLater(int idx) {
	m_zombiesToBeDeleted.push_back(idx);
}

void ZombieManager::AddZombie(const std::string& type, const std::string& name, int x, int y, int row) {
	auto zombie = ZombieFactory::CreateZombie(type, x, y, name);
	if (zombie) {
		zombie->m_selfIdx = s_zombieIdx;
		m_zombieLists[row][s_zombieIdx] = zombie;
		s_zombieIdx++;
	}
	else {
		std::cerr << "Failed to create zombie of type: " << type << std::endl;
	}
}

void ZombieManager::RemoveZombie(int idx) {
	// Search for zombie in all rows and remove it
	for (int row = 0; row < GAME_ROWS; row++) {
		auto it = m_zombieLists[row].find(idx);
		if (it != m_zombieLists[row].end()) {
			m_zombieLists[row].erase(it);
			return;
		}
	}
}

bool ZombieManager::HasZombieOutOfLeftBound() {
	// Check if any zombie has crossed the left boundary (game over)
	for (int row = 0; row < GAME_ROWS; ++row) {
		for (const auto& [id, zombie] : m_zombieLists[row]) {
			if (zombie && zombie->GetX() < 0) {
				return true;
			}
		}
	}
	return false;
}

void ZombieManager::CleanUp() {
	// Clear all zombies and reset state
	for (auto& row : m_zombieLists) {
		row.clear();
	}
	m_zombiesToBeAdded.clear();
	m_zombiesToBeDeleted.clear();
	s_zombieIdx = 0;
}