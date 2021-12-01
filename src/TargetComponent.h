#pragma once

#include "Component.h"
#include "Math.h"
#include <functional>

class Actor;
class SpriteComponent;
class ColliderComponent;

class TargetComponent : public Component {
public:
    TargetComponent(Actor* owner);
    void Select(const Vector4& reticleColor);
    void Deselect();
    bool IsSelected() const { return isSelected; }
private:
    SpriteComponent* sprite = nullptr;
    bool isSelected = false;

    std::function<void(TargetComponent*)> onDestroy = nullptr;
};
