#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include "pvz/Framework/ObjectBase.hpp"

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;

class GameObject : public ObjectBase {
public:
    GameObject(ImageID imageID, int x, int y, LayerID layer,
        int width, int height, AnimID animID,
        const std::string& name = "");

    virtual ~GameObject();

    virtual void Update() override;
    virtual void OnClick() override;


    std::string GetName() const;

private:
    std::string m_name;
};


class Background :
    public GameObject
{
public:
    Background(int x, int y)
        : GameObject(ImageID::BACKGROUND, x, y, LayerID::BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, AnimID::NO_ANIMATION,"backgound")
    {
    }
};





#endif // !GAMEOBJECT_HPP__




