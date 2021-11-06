#pragma once

#include "Component.h"

class Targetable : public Component {
public:
    Targetable(class Actor* owner);
    void Select();
    bool IsSelected() const { return isSelected; }
private:
    class SpriteComponent* sprite = nullptr;
    class ColliderComponent* collider = nullptr;
    bool isSelected = false;
};
