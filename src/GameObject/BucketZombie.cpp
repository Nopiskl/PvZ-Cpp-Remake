#include "pvz/GameObject/BucketZombie.h"
#include "pvz/GameObject/Zombie.h"

BucketZombie::BucketZombie(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : Zombie(imageID, x, y, layer, width, height, animID, name)
{
    constexpr int bucketZombieHP = 1300;  // High HP due to bucket armor
    HP = bucketZombieHP;
    m_zombie = "BucketZombie";
}

// Bucket zombie uses base zombie behavior but has much higher HP
void BucketZombie::Update()
{
    BasicUpdate();  // Same AI as regular zombie, just tankier
}