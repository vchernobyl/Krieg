#include "TargetComponent.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "ParticleComponent.h"
#include "Random.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"

TargetComponent::TargetComponent(Actor* owner, int health) : Component(owner), health(health) {
    sprite = new SpriteComponent(owner, 300);
    sprite->SetTexture(owner->GetGame()->GetRenderer()->GetTexture("data/textures/Circle.png"));
    sprite->SetEnabled(false);

    ownerSprite = owner->GetComponent<SpriteComponent>();
    originalColor = ownerSprite->GetColor();
}

void TargetComponent::Update(float deltaTime) {
    if (shouldFlash) {
        ownerSprite->SetColor(Color::Red);
        flashFrames--;
        if (flashFrames <= 0) {
            shouldFlash = false;
            ownerSprite->SetColor(originalColor);
        }
    } 
}

void TargetComponent::Damage(int amount) {
    shouldFlash = true;
    flashFrames = 8;
    health -= amount;

    if (health <= 0) {
        if (onDestroy) onDestroy(this);
        GetOwner()->SetState(Actor::State::Dead);
    }
}

void TargetComponent::Select() {
    isSelected = true;
    sprite->SetEnabled(isSelected);
}

void TargetComponent::Deselect() {
    isSelected = false;
    sprite->SetEnabled(isSelected);
}
