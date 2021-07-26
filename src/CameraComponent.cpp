#include "CameraComponent.h"
#include "Renderer.h"
#include "Actor.h"
#include "Game.h"

CameraComponent::CameraComponent(Actor* owner)
    : Component(owner) {}

void CameraComponent::Update(float deltaTime) {
    const auto target = owner->GetPosition();
    SetView(target);
}

void CameraComponent::SetView(const Vector2& view) {
    auto renderer = owner->GetGame()->GetRenderer();
    renderer->SetView(view);
}
