#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include "pvz/GameObject/Zombie.h"

class ZombieFactory {
public:
    using ZombieCreator = std::function<std::shared_ptr<Zombie>(int x, int y, const std::string& name)>;

    static void Register(const std::string& type, ZombieCreator creator);

    static std::shared_ptr<Zombie> CreateZombie(const std::string& type, int x, int y, const std::string& name);

private:
    static std::unordered_map<std::string, ZombieCreator>& GetRegistry();
};
