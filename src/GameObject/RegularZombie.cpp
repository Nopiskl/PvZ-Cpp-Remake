#include "pvz/GameObject/RegularZombie.h"
#include "pvz/GameObject/Zombie.h"

RegularZombie::RegularZombie(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : Zombie(imageID, x, y, layer, width, height, animID, name)
{
    constexpr int regularZombieHP = 200;
    HP = regularZombieHP;
    m_zombie = "RegularZombie";
}

// Regular zombie uses base zombie behavior (walk and eat)
void RegularZombie::Update()
{
    BasicUpdate();  // Standard zombie AI: move forward, eat plants when encountered
}