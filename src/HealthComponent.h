#pragma once

#include "Component.h"
#include "Math.h"
#include <functional>

class HealthComponent : public Component {
public:
    HealthComponent(class Actor* owner, int maxHealth);
    void Update(float deltaTime) override;

    int GetHealth() const { return health; }

    void ReceiveDamage(int damage);
    void SetOnDestroy(std::function<void()> onDestroy) { this->onDestroy = onDestroy; }
private:
    int health = 100;
    
    bool shouldFlash = false;
    int flashFrames = 0;
    Vector4 originalColor;

    class SpriteComponent* ownerSprite = nullptr;

    std::function<void()> onDestroy = nullptr;
};
