#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include "pvz/GameObject/Plant.h"

class GameWorld;

class PlantFactory {
public:
    using PlantCreator = std::function<std::shared_ptr<Plant>(int x, int y,  const std::string& name)>;

    static void Register(const std::string& type, PlantCreator creator);

    static std::shared_ptr<Plant> CreatePlant(const std::string& type, int x, int y, const std::string& name);

private:
    static std::unordered_map<std::string, PlantCreator>& GetRegistry();
};
