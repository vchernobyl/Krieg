#include "Enemy.h"
#include "Game.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

Enemy::Enemy(Game* game) : Actor(game) {
    SetScale(2.5f);
    SetPosition(Vector2(100, 700));

    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("assets/SpriteSheet.png"));
    sprite->SetDrawRegion(Rectangle(0, 16, 16, 16));

    auto collider = new BoxColliderComponent(this);
    collider->SetSize(Vector2(16, 16) * GetScale());

    rigidbody = new RigidbodyComponent(this);
}

void Enemy::UpdateActor(float deltaTime) {
    rigidbody->velocity.x = velocity * deltaTime;
}

void Enemy::OnCollisionEnter(const CollisionInfo& info) {
    // If hit a wall, just turn around.
    if (info.contactNormal == Vector2::Left || info.contactNormal == Vector2::Right) {
	velocity = -velocity;
	if (velocity > 0) {
	    sprite->flipX = false;
	} else {
	    sprite->flipX = true;
	}
    }
}

void Enemy::OnTriggerEnter(ColliderComponent* other) {
    SDL_Log("Enemy hit!");
}
