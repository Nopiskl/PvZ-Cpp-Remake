#pragma once

#include "pvz/GameObject/GameObject.hpp"

class Shovel : public GameObject
{
public:
    Shovel(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");
    virtual void OnClick() override;

private:
};