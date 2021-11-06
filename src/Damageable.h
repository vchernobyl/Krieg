#pragma once

#include "Component.h"

class Damageable : public Component {
public:
    Damageable(class Actor* owner, int health);
    void Damage(int amount);
private:
    int health;
};
