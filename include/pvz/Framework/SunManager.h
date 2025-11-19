#pragma once
#include <unordered_map>
#include <memory>
#include "pvz/GameObject/Sun.h"
#include "pvz/Framework/TextBase.hpp"
#include "pvz/Framework/ManagerBase.h"

 class SunManager : public ManagerBase {
    public:
        static SunManager& GetInstance();
        void AddSun(std::shared_ptr<Sun> sun);
        void RemoveSun(int id);
        void Update();
        void AddSunAmount(int amount);
        void SubtractSunAmount(int amount);
        int GetSunAmount() const;
        void CleanUp() override;

    private:
        SunManager() = default;
        ~SunManager() = default;
        SunManager(const SunManager&) = delete;
        SunManager& operator=(const SunManager&) = delete;
        std::shared_ptr<TextBase> Sun_Text = std::make_shared<TextBase>(60, WINDOW_HEIGHT - 78, "Initializing");
        std::unordered_map <int, std::shared_ptr<Sun>> sun_lists;
        int sun_amount = 0;
        int sun_generate_timer = 180;
        int sun_generate_time = 300;
 };