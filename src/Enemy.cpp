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
    sprite->SetDrawRegion(Rectangle(0, 0, 16, 16));

    rigidbody = new RigidbodyComponent(this, MotionType::Dynamic);

    auto size = sprite->GetSize() * GetScale();
    auto box = new BoxColliderComponent(this, size);
    box->SetCollisionFilter(CollisionCategory::Enemy,
			    CollisionCategory::Ground | CollisionCategory::Bullet);
}

void Enemy::UpdateActor(float deltaTime) {
}

// void Enemy::OnBeginContact(const Manifold& manifold) {
// }
