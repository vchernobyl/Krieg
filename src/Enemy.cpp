#include "Enemy.h"
#include "Game.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

Enemy::Enemy(Game* game) : Actor(game) {
    SetPosition(Vector2(5, 20));
    SetScale(2.0f);

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/Enemy.png"));

    rigidbody = new RigidbodyComponent(this, MotionType::Dynamic);

    auto size = sprite->GetSize() * GetScale();
    new BoxColliderComponent(this, size);
}

void Enemy::UpdateActor(float deltaTime) {
    float gravity = rigidbody->GetVelocity().y;
    rigidbody->SetVelocity(Vector2(-velocity, gravity));
}
