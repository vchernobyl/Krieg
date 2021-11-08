#include "Damageable.h"
#include "Actor.h"
#include "SpriteComponent.h"

Damageable::Damageable(Actor* owner, int health) : Component(owner), health(health) {
    ownerSprite = owner->GetComponent<SpriteComponent>();
    originalColor = ownerSprite->GetColor();
}

void Damageable::Update(float deltaTime) {
    if (shouldFlash) {
        ownerSprite->SetColor(Color::Red);
        flashFrames--;
        if (flashFrames <= 0) {
            shouldFlash = false;
            ownerSprite->SetColor(originalColor);
        }
    } 
}

void Damageable::Damage(int amount) {
    shouldFlash = true;
    flashFrames = 8;
    health -= amount;
    if (health <= 0) {
        GetOwner()->SetState(Actor::State::Dead);
    }
}
