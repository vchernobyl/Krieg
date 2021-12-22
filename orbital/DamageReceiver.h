#pragma once

#include <Engine.h>

class DamageReceiver : public Component {
public:
    DamageReceiver(Actor* owner, int maxHealth);
    void ReceiveDamage(int amount);
    int GetHealth() const { return health; }
private:
    int health;
};
