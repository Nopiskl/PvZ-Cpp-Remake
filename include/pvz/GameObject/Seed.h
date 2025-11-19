#pragma once
#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/GameObject.hpp"

class Seed : public GameObject {
 public:
        Seed(ImageID imageID, int x, int y, LayerID layer,
            int width, int height, AnimID animID,int cooldownTime,int cost,
            const std::string& name ="");
        virtual void OnClick() override;
        virtual void Update() override;
        int cost;
 private:
        bool m_isCoolingDown;
        int m_cooldownTime;     
        int m_cooldownTimer; 
        void CreateCooldownCover();
};

