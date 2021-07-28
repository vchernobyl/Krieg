#include "CameraComponent.h"
#include "Renderer.h"
#include "Actor.h"
#include "Game.h"

CameraComponent::CameraComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {
    position = Vector2::Zero;
    viewport = owner->GetGame()->GetRenderer()->GetWindowSize() * Game::PixelsToUnits;
}

void CameraComponent::Update(float deltaTime) {
    const auto target = owner->GetPosition() - viewport * 0.5f;
    const auto timeToTarget = 0.9f;
    const auto maxSpeed = 20.0f;

    position.x = Math::SmoothDamp(position.x, target.x, velocityX, timeToTarget, maxSpeed, deltaTime);
    position.y = Math::SmoothDamp(position.y, target.y, velocityY, timeToTarget, maxSpeed, deltaTime);    

    if (position.x < bounds.position.x) position.x = bounds.position.x;
    if (position.y < bounds.position.y) position.y = bounds.position.y;
    if (position.x > bounds.size.x - viewport.x) position.x = bounds.size.x - viewport.x;
    if (position.y > bounds.size.y - viewport.y) position.y = bounds.size.y - viewport.y;

    SetView(position);
}

void CameraComponent::SetView(const Vector2& view) {
    auto renderer = owner->GetGame()->GetRenderer();
    renderer->SetView(view);
}
