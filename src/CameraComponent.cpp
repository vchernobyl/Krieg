#include "CameraComponent.h"
#include "Renderer.h"
#include "Actor.h"
#include "Game.h"

CameraComponent::CameraComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {
    position = owner->GetPosition();
    viewport = owner->GetGame()->GetRenderer()->GetWindowSize() * Game::PixelsToUnits;
}

void CameraComponent::Update(float deltaTime) {
    auto target = owner->GetPosition() - viewport * 0.5f;

    // What if it's because of the '<', '>' operators?
    // if (target.x < bounds.position.x) target.x = bounds.position.x;
    // if (target.y < bounds.position.y) target.y = bounds.position.y;
    // if (target.x > bounds.size.x - viewport.x) target.x = bounds.size.x - viewport.x;
    // if (target.y > bounds.size.y - viewport.y) target.y = bounds.size.y - viewport.y;

    const float timeToTarget = 0.5f;
    const float maxSpeed = 20.0f;
    position.x = Math::SmoothDamp(position.x, target.x, velocityX, timeToTarget, maxSpeed, deltaTime);
    position.y = Math::SmoothDamp(position.y, target.y, velocityY, timeToTarget, maxSpeed, deltaTime);    

    SetView(position);
}

void CameraComponent::SetView(const Vector2& view) {
    auto renderer = owner->GetGame()->GetRenderer();
    renderer->SetView(view);
}
