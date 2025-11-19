#pragma once
#include "pvz/GameObject/GameObject.hpp"

class Explosion : public GameObject
{
public:
    int cnt = 0;
    Explosion(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name) : GameObject(imageID, x, y, layer, width, height, animID, name){}

private:
};