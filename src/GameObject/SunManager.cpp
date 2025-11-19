#include "pvz/Framework/SunManager.h"


SunManager& SunManager::GetInstance() {
    static SunManager instance;
    return instance;
}


void SunManager::AddSun(std::shared_ptr<Sun> obj) {
	sun_lists[obj->GetSelfIdx()] = obj;
}

int  SunManager::GetSunAmount() const
{
	return sun_amount;
}

void SunManager::RemoveSun(int idx)
{
	sun_lists.erase(idx);
}

void SunManager::AddSunAmount(int amount)
{
	sun_amount += amount;
}

void SunManager::SubtractSunAmount(int amount)
{
	sun_amount -= amount;
}


void SunManager::Update() {
    std::string sun_Amount_Text = std::to_string(GetSunAmount());
    Sun_Text->SetText(sun_Amount_Text);

    if (sun_generate_timer > 0) {
        sun_generate_timer--;
    }
    else {
        auto sun = std::make_shared<Sun>(
            ImageID::SUN,
            randInt(75, WINDOW_WIDTH - 75),
            WINDOW_HEIGHT - 35,
            LayerID::SUN,
            80, 80, AnimID::IDLE,
            false,
            "Sun"
        );
        AddSun(sun);
        sun_generate_timer = sun_generate_time;
    }

    std::vector<int> to_remove;
    for (auto& [id, obj] : sun_lists) {
        if (!obj) continue;

        if (obj->sun_falling_timer == 0 || obj->sun_flower_falling_timer == 0) {
            if (obj->on_ground_timer <= 300) {
                obj->on_ground_timer++;
            }
            else {
                to_remove.push_back(id);
            }
        }
        else {
            if (obj->is_sun_flower) {
                obj->sun_flower_falling_timer--;
                obj->vy -= 1;
                obj->MoveTo(obj->GetX() - 1, obj->GetY() + obj->vy);
            }
            else {
                obj->sun_falling_timer--;
                obj->MoveTo(obj->GetX(), obj->GetY() - 2);
            }
        }
    }

    for (int id : to_remove) {
        RemoveSun(id);
    }
}

void SunManager::CleanUp()
{
    sun_lists.clear();

    sun_amount = 500;
    sun_generate_timer = 0;
    sun_generate_time = 300;

    if (Sun_Text) {
        Sun_Text->SetText(std::to_string(sun_amount));
    }
}