#include "pvz/Framework/WaveManager.h"
#include "pvz/Framework/ZombieManager.h"


WaveManager& WaveManager::GetInstance() {
    static WaveManager instance;
    return instance;
}

void WaveManager::Update()
{
    ++tick_counter;

    // Stop spawning after max wave reached
    if (current_wave >= max_wave) {
        return;
    }

    // Start next wave when timer expires
    if (tick_counter >= next_wave_tick) {
        StartNextWave(); 
    }

    // Update wave display text
    UpdateWaveDisplay();
}

void WaveManager::UpdateWaveDisplay()
{
    std::string waveText = "Current Waves: " + std::to_string(current_wave);
    Wave_Text->SetText(waveText);
}

void WaveManager::StartNextWave() {
    ++current_wave;
    UpdateWaveDisplay();

    int zombieCount = CalculateZombieCount();
    SpawnZombiesForWave(zombieCount);
    ScheduleNextWave();
}

int WaveManager::CalculateZombieCount() const
{
    // Zombie count increases gradually with wave number
    return (15 + current_wave) / 10;
}

std::string WaveManager::SelectZombieType() const
{
    // Probability weights for different zombie types
    constexpr int regularWeight = 20;
    const int poleVaultWeight = 2 * std::max(current_wave - 8, 0);
    const int bucketWeight = 3 * std::max(current_wave - 15, 0);
    const int totalWeight = regularWeight + poleVaultWeight + bucketWeight;

    // Random selection based on weighted probabilities
    int roll = randInt(1, totalWeight);
    
    if (roll <= regularWeight) {
        return "RegularZombie";
    }
    else if (roll <= regularWeight + poleVaultWeight) {
        return "PoleVaultZombie";
    }
    else {
        return "BucketZombie";
    }
}

void WaveManager::SpawnZombiesForWave(int count)
{
    for (int i = 0; i < count; ++i) {
        std::string zombieType = SelectZombieType();
        
        // Random spawn position at right edge
        int x = randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1);
        int row = randInt(0, GAME_ROWS - 1);
        int y = FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT;

        ZombieManager::GetInstance().AddZombieLater(zombieType, zombieType, x, y, row);
    }
}

void WaveManager::ScheduleNextWave()
{
    // Wave interval decreases as game progresses (gets harder)
    int waveInterval = std::max(150, 600 - 20 * current_wave);
    next_wave_tick = tick_counter + waveInterval;
}

void WaveManager::CleanUp()
{
    current_wave = 0;
    tick_counter = 0;
}