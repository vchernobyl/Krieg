#include "Health.h"

Health::Health(Actor* owner, int maxHealth)
    : Component(owner), health(maxHealth) {
}

void Health::ReceiveDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        GetOwner()->SetState(Actor::State::Dead);
        health = 0;
        if (onZeroHealth) onZeroHealth();
    }
    
    if (onReceiveDamage) onReceiveDamage();
}
