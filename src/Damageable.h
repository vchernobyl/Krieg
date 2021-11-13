#pragma once

#include "Component.h"
#include "Math.h"
#include <functional>

class Actor;
class SpriteComponent;
class ColliderComponent;

class Damageable : public Component {
public:
    Damageable(Actor* owner, int health);
    void Update(float deltaTime) override;
    void Damage(int amount);
    void Select();
    void Deselect();
    bool IsSelected() const { return isSelected; }

    // BUG: If multiple weapons are targetting the same enemy, setting this lambda will override
    // previously set lambda by the previous weapon system. This will retain the target in the list
    // even after it is destroyed for all but one weapon system.
    void SetOnDestroy(std::function<void(Damageable*)> onDestroy) { this->onDestroy = onDestroy; }

private:
    int health = 100;

    bool shouldFlash = false;
    int flashFrames = 0;
    Vector4 originalColor;

    SpriteComponent* ownerSprite = nullptr;
    SpriteComponent* sprite = nullptr;
    ColliderComponent* collider = nullptr;
    bool isSelected = false;

    std::function<void(Damageable*)> onDestroy = nullptr;
};
