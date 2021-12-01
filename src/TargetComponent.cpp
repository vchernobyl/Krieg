#include "TargetComponent.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"

TargetComponent::TargetComponent(Actor* owner) : Component(owner) {
    sprite = new SpriteComponent(owner, 300);
    sprite->SetTexture(owner->GetGame()->GetRenderer()->GetTexture("data/textures/Circle.png"));
    sprite->SetEnabled(false);
}

void TargetComponent::Select(const Vector4& reticleColor) {
    isSelected = true;
    sprite->SetEnabled(isSelected);
    sprite->SetColor(reticleColor);
}

void TargetComponent::Deselect() {
    isSelected = false;
    sprite->SetEnabled(isSelected);
}
