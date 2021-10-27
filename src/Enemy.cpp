#include "Enemy.h"
#include "Texture.h"
#include "Renderer.h"
#include "DebugRenderer.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"
#include <cassert>

Enemy::Enemy(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));
    sprite->SetColor(Color::Red);

    outline = new SpriteComponent(this, 200);
    outline->SetTexture(game->GetRenderer()->GetTexture("data/textures/Circle.png"));
    outline->SetEnabled(false);

    auto collider = new CircleColliderComponent(this, Vector2::Zero, 0.5f);
    rigidbody = collider->GetAttachedRigidbody();
    followTarget = game->GetActorByTag("Player");

    assert(followTarget);
    assert(rigidbody);
}

void Enemy::UpdateActor(float deltaTime) {
    auto direction = followTarget->GetPosition() - GetPosition();
    direction.Normalize();

    const auto movementSpeed = 50.0f;
    rigidbody->SetVelocity(direction * movementSpeed * deltaTime);
    SetRotation(Math::Atan2(direction.y, direction.x));

    DebugRenderer::DrawLine(GetPosition(), GetPosition() + GetForward(), Color::Red);
}

void Enemy::Select() {
    isSelected = !isSelected;
    outline->SetEnabled(isSelected);
}
