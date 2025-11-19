#pragma once
#include "pvz/GameObject/GameObject.hpp"

class SunManager;

class Sun : public GameObject {
public:
    static int s_idx;
    bool is_sun_flower = false;
    int sun_flower_falling_timer = 12;
    int sun_falling_timer = randInt(63, 263);
    int vy = 4;
    int on_ground_timer = 0;

    Sun(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID, bool is_sunflower,
        const std::string& name = "");

    void OnClick() override;
    int GetSelfIdx() const { return m_selfIdx; }

private: 
    int m_selfIdx;
};