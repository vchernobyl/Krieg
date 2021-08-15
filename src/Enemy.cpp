#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

Enemy::Enemy(Game* game) : Actor(game) {
    SetPosition(Vector2(5, 20));
    SetScale(2.0f);

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/Enemy.png"));

    rigidbody = new RigidbodyComponent(this, MotionType::Dynamic);

    auto size = sprite->GetSize() * GetScale();
    auto box = new BoxColliderComponent(this, size);
    box->SetCollisionFilter(CollisionCategory::Enemy,
			    CollisionCategory::Ground | CollisionCategory::Bullet);
}

void Enemy::UpdateActor(float deltaTime) {
    if (isHit) {
	hitTime += deltaTime;

	// Flash the enemy for 3 full frames.
	if (hitTime >= 0.016f * 3.0f) {
	    hitTime = 0.0f;
	    isHit = false;
	}
    }
}

void Enemy::OnBeginContact(const Contact& contact) {
    if (dynamic_cast<Bullet*>(contact.other)) {
	isHit = true;
    }
}
