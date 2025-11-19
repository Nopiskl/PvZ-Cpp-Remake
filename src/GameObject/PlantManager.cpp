#include "pvz/Framework/PlantManager.h"
#include "pvz/Framework/StateManager.h"
#include "pvz/GameObject/Seed.h"

PlantManager& PlantManager::GetInstance() {
    static PlantManager instance;
    return instance;
}

void PlantManager::Init()
{
	RegisterPlantFactory();
	InitializeSeeds();
}

void PlantManager::InitializeSeeds()
{
	// Seed configurations: name, image, x offset, cooldown, sun cost
	const std::vector<SeedConfig> seedConfigs = {
		{"Sunflower",   ImageID::SEED_SUNFLOWER,    0,   240,  50},
		{"Peashooter",  ImageID::SEED_PEASHOOTER,   60,  240,  100},
		{"Wallnut",     ImageID::SEED_WALLNUT,      120, 900,  50},
		{"CherryBomb",  ImageID::SEED_CHERRY_BOMB,  180, 1200, 150},
		{"Repeater",    ImageID::SEED_REPEATER,     240, 240,  200}
	};

	for (const auto& config : seedConfigs) {
		CreateSeedPacket(config);
	}
}

void PlantManager::CreateSeedPacket(const SeedConfig& config)
{
	const int baseX = 130;
	const int yPosition = WINDOW_HEIGHT - 44;
	const int seedWidth = 50;
	const int seedHeight = 70;

	auto seed = std::make_shared<Seed>(
		config.seedImageID,
		baseX + config.xOffset,
		yPosition,
		LayerID::UI,
		seedWidth,
		seedHeight,
		AnimID::NO_ANIMATION,
		config.cooldown,
		config.sunCost,
		config.name
	);
	
	AddSeed(config.name, seed);
}

void PlantManager::RegisterPlantFactory()
{
	// Common plant properties
	constexpr int plantWidth = 60;
	constexpr int plantHeight = 80;
	constexpr LayerID plantLayer = LayerID::PLANTS;
	constexpr AnimID plantAnim = AnimID::IDLE;

	// Register all plant types with their factory creators
	PlantFactory::Register("Sunflower", [=](int x, int y, const std::string& name) {
		return std::make_shared<Sunflower>(ImageID::SUNFLOWER, x, y, plantLayer, plantWidth, plantHeight, plantAnim, name);
	});

	PlantFactory::Register("Wallnut", [=](int x, int y, const std::string& name) {
		return std::make_shared<Wallnut>(ImageID::WALLNUT, x, y, plantLayer, plantWidth, plantHeight, plantAnim, name);
	});

	PlantFactory::Register("Peashooter", [=](int x, int y, const std::string& name) {
		return std::make_shared<Peashooter>(ImageID::PEASHOOTER, x, y, plantLayer, plantWidth, plantHeight, plantAnim, name);
	});

	PlantFactory::Register("Repeater", [=](int x, int y, const std::string& name) {
		return std::make_shared<Repeater>(ImageID::REPEATER, x, y, plantLayer, plantWidth, plantHeight, plantAnim, name);
	});

	PlantFactory::Register("CherryBomb", [=](int x, int y, const std::string& name) {
		return std::make_shared<CherryBomb>(ImageID::CHERRY_BOMB, x, y, plantLayer, plantWidth, plantHeight, plantAnim, name);
	});
}


void PlantManager::Update()
{
	// Update all active plants
	for (auto& [name, plant] : m_plantLists) {
		if (plant) {
			plant->Update();
		}
	}

	// Update all seed packets
	for (auto& [name, seed] : m_seedLists) {
		if (seed) {
			seed->Update();
		}
	}

	// Process deferred operations to avoid iterator invalidation
	ProcessPendingDeletions();
	ProcessPendingAdditions();
}

void PlantManager::ProcessPendingDeletions()
{
	for (const std::string& name : m_plantsToBeDeleted) {
		RemovePlant(name);
	}
	m_plantsToBeDeleted.clear();
}

void PlantManager::ProcessPendingAdditions()
{
	for (const auto& [type, name, x, y] : m_plantsToBeAdded) {
		AddPlant(type, name, x, y);
	}
	m_plantsToBeAdded.clear();
}

void PlantManager::AddPlantLater(const std::string& type, const std::string& name, int x, int y) {
	m_plantsToBeAdded.emplace_back(type, name, x, y);
}

void PlantManager::RemovePlantLater(const std::string& name) {
	m_plantsToBeDeleted.push_back(name);
}

void PlantManager::AddSeed(const std::string& name, std::shared_ptr<Seed> seed) {
	m_seedLists[name] = seed;
}

void PlantManager::AddPlant(const std::string& type, const std::string& name, int x, int y) {
	auto plant = PlantFactory::CreatePlant(type, x, y, name);
	if (plant) {
		m_plantLists[name] = plant;
	}
	else {
		std::cerr << "Failed to create plant of type: " << type << std::endl;
	}
}

void PlantManager::RemovePlant(const std::string& name) {
	m_plantLists.erase(name);
}

void PlantManager::SetPlantingSiteState(int row, int col, bool state)
{
	if (row >= 0 && row < GAME_ROWS && col >= 0 && col < GAME_COLS) {
		m_plantingGrid[row][col].second->SetSiteState(state);
	}
}

void PlantManager::AddPlantingSite(int row, int col, const std::string& idx, std::shared_ptr<PlantingSite> site)
{
	site->m_row = row;
	site->m_col = col;
	m_plantingGrid[row][col] = std::make_pair(idx, site);
}

bool PlantManager::IsHoldingShovel() const
{
	return StateManager::GetInstance().Mouse_state.IsHoldingShovel;
}

void PlantManager::SetHoldingPlantState(bool state)
{
	StateManager::GetInstance().Mouse_state.IsHoldingUnplantedSeed = state;
}

void PlantManager::SetHoldingShovelState()
{
	auto& mouseState = StateManager::GetInstance().Mouse_state;
	mouseState.IsHoldingShovel = !mouseState.IsHoldingShovel;
}

bool PlantManager::IsHoldingUnplantedSeed() const
{
	return StateManager::GetInstance().Mouse_state.IsHoldingUnplantedSeed;
}

PlantManager::PlantManager()
{
	InitializePlantingGrid();
}

void PlantManager::InitializePlantingGrid()
{
	// Resize grid to game dimensions
	m_plantingGrid.resize(GAME_ROWS, std::vector<PlantSlot>(GAME_COLS));

	// Create planting sites for each grid cell
	for (int row = 0; row < GAME_ROWS; ++row) {
		for (int col = 0; col < GAME_COLS; ++col) {
			int x = FIRST_COL_CENTER + col * LAWN_GRID_WIDTH;
			int y = FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT;
			std::string gridIndex = std::to_string(row) + "," + std::to_string(col);
			
			auto site = std::make_shared<PlantingSite>(
				ImageID::NONE, x, y, LayerID::UI, 
				60, 80, AnimID::NO_ANIMATION, gridIndex
			);
			
			AddPlantingSite(row, col, "", site);
		}
	}
}

void PlantManager::CleanUp() {
	// Clear all plant and seed collections
	m_plantLists.clear();
	m_seedLists.clear();
	m_plantsToBeAdded.clear();
	m_plantsToBeDeleted.clear();
	HoldingPlant.clear();

	// Reset player state
	SetHoldingPlantState(false);
	if (IsHoldingShovel()) {
		SetHoldingShovelState();
	}
}