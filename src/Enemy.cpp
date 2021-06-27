#include "Enemy.h"
#include "Game.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

Enemy::Enemy(Game* game) : Actor(game) {
    SetPosition(Vector2(100, 700));

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/Enemy.png"));

    rigidbody = new RigidbodyComponent(this, MotionType::PhysicsDriven);

    auto collider = new BoxColliderComponent(this);
    auto size = sprite->GetSize() * GetScale();
    collider->SetBox(size.x, size.y);
}

void Enemy::UpdateActor(float deltaTime) {
    // float gravity = rigidbody->GetVelocity().y;
    // rigidbody->SetVelocity(Vector2(-velocity, gravity));
}
