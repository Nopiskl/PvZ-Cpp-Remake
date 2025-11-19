#pragma once
#include "pvz/GameObject/GameObject.hpp"
#include <map>
#include "pvz/GameObject/Zombie.h"


class Pea : public GameObject
{
public:
    bool is_dead = false;
    Pea(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,int row,int idx,
        const std::string& name = "");
    virtual void OnClick() override;
    void Update() override; 

    bool IsColliding(int x1, int width1, int x2, int width2) {
        return x1 < x2 + width2 && x1 + width1 > x2;
    }

private:
    int m_row = -1;
    int m_selfIdx = 0;
    std::map<int, std::shared_ptr<Zombie>> m_rowZombies;
};