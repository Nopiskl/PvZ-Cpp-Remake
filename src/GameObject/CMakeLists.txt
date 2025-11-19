cmake_minimum_required(VERSION 3.16)

add_library(
  GameObject
  STATIC
  GameObject.cpp
  BucketZombie.cpp
  CherryBomb.cpp
  Pea.cpp
  PeaManager.cpp
  Peashooter.cpp
  Plant.cpp
  PlantFactory.cpp
  PlantingSite.cpp
  PlantManager.cpp
  PoleVaultZombie.cpp
  RegularZombie.cpp
  Repeater.cpp
  Seed.cpp
  Shovel.cpp
  StateManager.cpp
  Sun.cpp
  Sunflower.cpp
  SunManager.cpp
  Wallnut.cpp
  WaveManager.cpp
  Zombie.cpp
  ZombieFactory.cpp
  ZombieManager.cpp
)

target_link_libraries(
  GameObject
  Framework
)
