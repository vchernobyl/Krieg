#include "CameraComponent.h"
#include "Renderer.h"
#include "Actor.h"
#include "Game.h"

CameraComponent::CameraComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {
    viewport = owner->GetGame()->GetRenderer()->GetWindowSize() * Game::PixelsToUnits;
}

void CameraComponent::Update(float deltaTime) {
    const auto target = owner->GetPosition() - viewport * 0.5f;
    const auto timeToTarget = 0.25;
    const auto maxSpeed = 20.0f;

    position.x = Math::SmoothDamp(position.x, target.x, velocityX, timeToTarget, maxSpeed, deltaTime);
    position.y = Math::SmoothDamp(position.y, target.y, velocityY, timeToTarget, maxSpeed, deltaTime);    

    position.x = Math::Clamp(position.x, bounds.position.x, bounds.size.x - viewport.x);
    position.y = Math::Clamp(position.y, bounds.position.y, bounds.size.y - viewport.y);

    SetView(position);
}

void CameraComponent::SetView(const Vector2& view) {
    auto renderer = owner->GetGame()->GetRenderer();
    renderer->SetView(view);
}
