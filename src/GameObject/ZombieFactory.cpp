#include "pvz/FrameWork/ZombieFactory.h"
#include "pvz/GameObject/Zombie.h"
#include "pvz/GameObject/RegularZombie.h"


std::unordered_map<std::string, ZombieFactory::ZombieCreator>& ZombieFactory::GetRegistry() {
    static std::unordered_map<std::string, ZombieCreator> registry;
    return registry;
}

void ZombieFactory::Register(const std::string& type, ZombieCreator creator) {
    GetRegistry()[type] = creator;
}

std::shared_ptr<Zombie> ZombieFactory::CreateZombie(const std::string& type, int x, int y, const std::string& name) {
    auto& registry = GetRegistry();
    auto it = registry.find(type);
    if (it != registry.end()) {
        return it->second(x, y, name);
    }
    return nullptr;
}


