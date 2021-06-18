#include "Enemy.h"
#include "Game.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Collision.h"

Enemy::Enemy(Game* game) : Actor(game) {
    SetScale(2.5f);
    SetPosition(Vector2(100, 700));

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/SpriteSheet.png"));
    sprite->SetDrawRegion(Rectangle(0, 16, 16, 16));

    rigidbody = new RigidbodyComponent(this, MotionType::PhysicsDriven);

    auto collider = new BoxColliderComponent(this);
    auto size = Vector2(16, 16) * GetScale();
    collider->SetBox(size.x, size.y);
}

void Enemy::UpdateActor(float deltaTime) {
    float gravity = rigidbody->GetVelocity().y;
    rigidbody->SetVelocity(Vector2(-velocity, gravity));
}
