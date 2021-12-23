#pragma once

#include <Engine.h>
#include <functional>

class Health : public Component {
public:
    Health(Actor* owner, int maxHealth);

    void ReceiveDamage(int amount);
    void SetOnReceiveDamage(std::function<void()> fn) { onReceiveDamage = fn; }
    void SetOnZeroHealth(std::function<void()> fn) { onZeroHealth = fn; }

    int GetHealth() const { return health; }
private:
    int health;

    std::function<void()> onReceiveDamage;
    std::function<void()> onZeroHealth;
};
