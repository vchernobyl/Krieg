#pragma once

#include "Component.h"
#include "Math.h"

class Damageable : public Component {
public:
    Damageable(class Actor* owner, int health);
    void Update(float deltaTime) override;
    void Damage(int amount);
private:
    int health = 100;

    bool shouldFlash = false;
    int flashFrames = 0;
    Vector4 originalColor;
    class SpriteComponent* ownerSprite = nullptr;
};
