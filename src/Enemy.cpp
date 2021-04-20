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

    rigidbody = new RigidbodyComponent(this);
}

void Enemy::ActorInput(const InputState& input) {
    velocity = Vector2::Zero;
    
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_D)) velocity.x = 100.0f;
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_A)) velocity.x = -100.0f;
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_W)) velocity.y = -350.0f;
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_S)) velocity.y = 350.0f;
}

void Enemy::UpdateActor(float deltaTime) {
    rigidbody->velocity.x = velocity.x * deltaTime;
    rigidbody->velocity.y = velocity.y * deltaTime;
}
