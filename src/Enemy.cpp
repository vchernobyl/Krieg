#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"

Enemy::Enemy(Game* game) : Actor(game) {
    SetScale(2.5f);
    SetPosition(Vector2(900, 600));

    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetTexture("assets/SpriteSheet.png"));
    sprite->SetRegion({ 0, 16, 16, 16 });

    auto collider = new BoxColliderComponent(this);
    collider->SetSize(Vector2(16, 16) * GetScale());

    rigidbody = new RigidbodyComponent(this);
}

void Enemy::UpdateActor(float deltaTime) {
    time += deltaTime;
    rigidbody->velocity.x = velocity * deltaTime;

    if (time > 4.0f) {
	time = 0.0f;
	velocity = -velocity;
    }
}
