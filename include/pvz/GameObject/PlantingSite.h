#pragma once

#include "pvz/GameObject/GameObject.hpp"

class PlantingSite : public GameObject
{
public:
    PlantingSite(ImageID imageID, int x, int y, LayerID layer,
            int width, int height, AnimID animID,
            const std::string& name = "");
    int m_row = 0;
    int m_col = 0;
    //std::string m_plant_on = "";
    void OnClick() override;
    void SetSiteState(bool state);
    bool GetPlantSite() { return has_plant; };

private:
    bool has_plant = false;
};