#pragma once

#include <Engine.h>
#include <functional>

class Health : public Component {
public:
    std::function<void()> onDamage;
    std::function<void()> onDie;

    Health(Actor* owner, int maxHealth);

    void ReceiveDamage(int amount);
    int GetHealth() const { return health; }
    void AddHealth(int amount);

private:
    int maxHealth;
    int health;
};
