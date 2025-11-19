#include "pvz/GameObject/GameObject.hpp"

// Your everything begins from here.
GameObject::GameObject(ImageID imageID, int x, int y, LayerID layer,
    int width, int height, AnimID animID,
    const std::string& name)
    : ObjectBase(imageID, x, y, layer, width, height, animID),
    m_name(name){
}

GameObject::~GameObject() {
}

void GameObject::Update() {
}

void GameObject::OnClick() {

    std::cout << "GameObject [" << m_name << "] was clicked.\n";
}

std::string GameObject::GetName() const {
    return m_name;
}
