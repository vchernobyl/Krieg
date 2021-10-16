#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

Enemy::Enemy(Game* game) : Actor(game) {
    SetPosition(Vector2::Zero);

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/Enemy.png"));

    new BoxColliderComponent(this, Vector2(2.0f, 1.0f) * GetScale());
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
