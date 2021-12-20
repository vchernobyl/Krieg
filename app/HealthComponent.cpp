#include "HealthComponent.h"
#include "Actor.h"
#include "SpriteComponent.h"

HealthComponent::HealthComponent(Actor* owner, int maxHealth)
    : Component(owner), health(maxHealth) {
    ownerSprite = owner->GetComponent<SpriteComponent>();
    originalColor = ownerSprite->GetColor();
}

void HealthComponent::Update(float deltaTime) {
    if (shouldFlash) {
        ownerSprite->SetColor(Color::Red);
        flashFrames--;
        if (flashFrames <= 0) {
            shouldFlash = false;
            ownerSprite->SetColor(originalColor);
        }
    } 
}

void HealthComponent::ReceiveDamage(int damage) {
    shouldFlash = true;
    flashFrames = 8;
    health -= damage;

    if (health <= 0) {
        if (onDestroy) onDestroy();
        GetOwner()->SetState(Actor::State::Dead);
    }
}

