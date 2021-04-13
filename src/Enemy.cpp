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
    rigidbody->isKinematic = false;
}

void Enemy::ActorInput(const InputState& input) {
    velocity = Vector2::Zero;
    
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_D)) velocity.x = 100.0f;
    if (input.Keyboard.GetKeyValue(SDL_SCANCODE_A)) velocity.x = -100.0f;
    if (input.Keyboard.GetKeyState(SDL_SCANCODE_W) == Pressed) velocity.y = -350.0f;
    
    rigidbody->velocity = Vector2(velocity.x, rigidbody->velocity.y + velocity.y);
}
