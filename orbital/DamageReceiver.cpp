#include "DamageReceiver.h"
#include <SDL/SDL.h>

DamageReceiver::DamageReceiver(Actor* owner, int maxHealth)
    : Component(owner), health(maxHealth) {
}

void DamageReceiver::ReceiveDamage(int amount) {
    SDL_Log("damage received");

    health -= amount;
    if (health <= 0) {
        GetOwner()->SetState(Actor::State::Dead);
        health = 0;
        if (onZeroHealth) onZeroHealth();
    }
    
    if (onReceiveDamage) onReceiveDamage();
}
