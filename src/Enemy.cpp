#include "Enemy.h"
#include "Texture.h"
#include "Renderer.h"
#include "DebugRenderer.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Targetable.h"
#include "Damageable.h"
#include <cassert>
#include "RocketLauncher.h"

Enemy::Enemy(Game* game) : Actor(game) {
    SetScale(0.75f);

    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));

    auto collider = new CircleColliderComponent(this, 0.5f * GetScale());
    collider->SetCollisionFilter(CollisionCategory::Enemy);
    rigidbody = collider->GetAttachedRigidbody();
    followTarget = game->GetActorByTag("Player");

    rocketLauncher = new RocketLauncher(game);

    new Targetable(this);
    new Damageable(this, 100);

    assert(followTarget);
    assert(rigidbody);
}

void Enemy::UpdateActor(float deltaTime) {
    rocketLauncher->SetPosition(GetPosition());
    rocketLauncher->SetRotation(GetRotation());
    
    auto direction = followTarget->GetPosition() - GetPosition();
    direction.Normalize();

    const auto movementSpeed = 50.0f;
    rigidbody->SetVelocity(direction * movementSpeed * deltaTime);
    SetRotation(Math::Atan2(direction.y, direction.x));

    DebugRenderer::DrawLine(GetPosition(), GetPosition() + GetForward(), Color::Red);
    DebugRenderer::DrawCircle(GetPosition(), visionRadius, Vector4(1.0f, 1.0f, 0.0f, 0.25f));
}

void Enemy::Attack() {
    auto dist = Vector2::Distance(followTarget->GetPosition(), GetPosition());
//    SDL_Log("distance=%f", dist);
    if (Vector2::Distance(followTarget->GetPosition(), GetPosition()) <= visionRadius) {
        SDL_Log("attack");
        rocketLauncher->AddTarget(followTarget);
    }
}
