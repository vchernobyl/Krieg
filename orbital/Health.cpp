#include "Health.h"

Health::Health(Actor* owner, int maxHealth)
    : Component(owner), maxHealth(maxHealth), health(maxHealth) {
}

void Health::ReceiveDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        GetOwner()->SetState(Actor::State::Dead);
        health = 0;
        if (onDie) onDie();
    }
    
    if (onDamage) onDamage();
}

void Health::AddHealth(int amount) {
    health += amount;
    if (health > maxHealth) {
	health = maxHealth;
    }
}
