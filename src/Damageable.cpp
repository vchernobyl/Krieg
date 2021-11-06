#include "Damageable.h"
#include "Actor.h"

Damageable::Damageable(Actor* owner, int health) : Component(owner), health(health) {
}

void Damageable::Damage(int amount) {
    health -= amount;
    if (health <= 0) {
        GetOwner()->SetState(Actor::State::Dead);
    }
}
