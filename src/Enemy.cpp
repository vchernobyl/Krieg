#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"

Enemy::Enemy(Game* game) : Actor(game) {
    SetScale(0.5f);
    SetPosition(Vector2(900, 600));

    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetTexture("assets/Enemy.png"));

    auto collider = new BoxColliderComponent(this);
    collider->SetSize(Vector2(32, 64));

    auto rigidbody = new RigidbodyComponent(this);
    rigidbody->isKinematic = false;
}
