#include "Enemy.h"
#include "Texture.h"
#include "Renderer.h"
#include "DebugRenderer.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"
#include "TargetComponent.h"
#include "HealthComponent.h"
#include "RocketLauncher.h"
#include "AudioComponent.h"
#include <cassert>

Projectile::Projectile(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Laser.png"));

    auto collider = new CircleColliderComponent(this, 0.2f * GetScale());
    collider->SetCollisionFilter(CollisionCategory::Bullet, CollisionCategory::Player |
                                 CollisionCategory::Ground);
    collider->SetSensor(true);

    rigidbody = collider->GetAttachedRigidbody();
}

void Projectile::UpdateActor(float deltaTime) {
    lifeTime -= deltaTime;
    if (lifeTime <= 0.0f) {
        SetState(Actor::State::Dead);
    }
}

void Projectile::OnBeginContact(const Contact& contact) {
    if (auto target = contact.other->GetComponent<HealthComponent>()) {
        target->ReceiveDamage(0);
    }
    SetState(Actor::State::Dead);
}

Enemy::Enemy(Game* game) : Actor(game) {
    SetScale(0.75f);

    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));

    auto collider = new CircleColliderComponent(this, 0.5f * GetScale());
    collider->SetCollisionFilter(CollisionCategory::Enemy);
    rigidbody = collider->GetAttachedRigidbody();
    followTarget = game->GetActorByTag("Player");

    new TargetComponent(this);
    new HealthComponent(this, 100);

    audio = new AudioComponent(this);

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
    DebugRenderer::DrawCircle(GetPosition(), visionRadius, Vector4(1.0f, 1.0f, 0.0f, 0.25f));

    auto distance = Vector2::Distance(followTarget->GetPosition(), GetPosition());
    if (distance <= visionRadius) {
        time += deltaTime;
        if (time >= fireRate) {
            time = 0.0f;
            ShootAt(followTarget->GetPosition());
        }
    }
}

void Enemy::ShootAt(const Vector2& position) {
    auto projectile = new Projectile(GetGame());
    projectile->SetPosition(GetPosition());
    projectile->SetRotation(GetRotation());

    auto direction = position - GetPosition();
    direction.Normalize();
    
    projectile->rigidbody->SetVelocity(direction * 10.0f);
    audio->PlayEvent("event:/Laser_Shot");
}
