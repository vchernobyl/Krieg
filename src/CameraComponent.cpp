#include "CameraComponent.h"
#include "Renderer.h"
#include "Actor.h"
#include "Game.h"

CameraComponent::CameraComponent(Actor* owner)
    : Component(owner) {
    position = Vector2(20, 20);//owner->GetPosition();
    viewport = owner->GetGame()->GetRenderer()->GetWindowSize() * Game::PixelsToUnits;
}

void CameraComponent::Update(float deltaTime) {
    auto target = owner->GetPosition() - viewport * 0.5f;

    if (target.x < bounds.position.x) target.x = bounds.position.x;
    if (target.y < bounds.position.y) target.y = bounds.position.y;
    if (target.x > bounds.size.x - viewport.x) target.x = bounds.size.x - viewport.x;
    if (target.y > bounds.size.y - viewport.y) target.y = bounds.size.y - viewport.y;

    const float lerp = 3.0f;
    position = Vector2::Lerp(position, target, lerp * deltaTime);

    SetView(position);
}

void CameraComponent::SetView(const Vector2& view) {
    auto renderer = owner->GetGame()->GetRenderer();
    renderer->SetView(view);
}
