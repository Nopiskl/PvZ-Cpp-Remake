#include "pvz/FrameWork/PlantFactory.h"
#include "pvz/GameObject/Sun.h"
#include "pvz/GameObject/Plant.h"
#include "pvz/GameObject/Wallnut.h"
#include "pvz/GameObject/Peashooter.h"
#include "pvz/GameObject/CherryBomb.h"
#include "pvz/GameObject/Repeater.h"
#include "pvz/GameObject/Sunflower.h"

std::unordered_map<std::string, PlantFactory::PlantCreator>& PlantFactory::GetRegistry() {
    static std::unordered_map<std::string, PlantCreator> registry;
    return registry;
}

void PlantFactory::Register(const std::string& type, PlantCreator creator) {
    GetRegistry()[type] = creator;
}

std::shared_ptr<Plant> PlantFactory::CreatePlant(const std::string& type, int x, int y,const std::string& name) {
    auto& registry = GetRegistry();
    auto it = registry.find(type);
    if (it != registry.end()) {
        return it->second(x, y, name);
    }
    return nullptr;
}
