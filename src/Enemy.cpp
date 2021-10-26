#include "Enemy.h"
#include "Texture.h"
#include "Renderer.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Assert.h"
#include <cassert>

Enemy::Enemy(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    auto texture = game->GetRenderer()->GetTexture("data/textures/Ship.png");
    sprite->SetTexture(texture);
    sprite->SetColor(Color::Red);
    SetPosition(Vector2(1.0f, 1.5f));

    auto collider = new CircleColliderComponent(this, Vector2::Zero, 0.5f);
    rigidbody = collider->GetAttachedRigidbody();
    followTarget = game->GetActorByTag("Player");

    assert(followTarget);
    assert(rigidbody);
}

void Enemy::UpdateActor(float deltaTime) {
    auto direction = followTarget->GetPosition() - GetPosition();
    direction.Normalize();

    rigidbody->SetVelocity(direction * 25.0f * deltaTime);
}
