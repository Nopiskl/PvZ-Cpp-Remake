#pragma once

#include <unordered_map>
#include <memory>
#include "pvz/Framework/TextBase.hpp"
#include "pvz/Framework/ManagerBase.h"


class WaveManager : public ManagerBase {
public:
    // Get singleton instance
    static WaveManager& GetInstance();
    
    // Update wave spawning logic each frame
    void Update();
    
    // Start spawning the next wave of zombies
    void StartNextWave();
    
    // Get the current wave number
    int GetCurrentWave() const { return current_wave; }
    
    // Clean up wave manager and reset state
    void CleanUp() override;
    
    std::shared_ptr<TextBase> Wave_Text = std::make_shared<TextBase>(WINDOW_WIDTH - 160, 8, "Current Waves: ", 255);

private:
    WaveManager() = default;
    ~WaveManager() = default;
    WaveManager(const WaveManager&) = delete;
    WaveManager& operator=(const WaveManager&) = delete;
    
    // Update the wave display text
    void UpdateWaveDisplay();
    
    // Calculate number of zombies for current wave
    int CalculateZombieCount() const;
    
    // Select zombie type based on wave progression
    std::string SelectZombieType() const;
    
    // Spawn specified number of zombies for the wave
    void SpawnZombiesForWave(int count);
    
    // Schedule when the next wave should start
    void ScheduleNextWave();
    
    int next_wave_tick = 1200;
    int tick_counter = 0;
    int current_wave = 0;
    int max_wave = 30;
};