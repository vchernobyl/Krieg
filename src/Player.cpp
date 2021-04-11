#include "Player.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"

Player::Player(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetTexture("assets/adventurer-idle-00.png"));
    
    SetPosition(Vector2(300, 150));
    SetScale(1.5f);
    
    auto collider = new BoxColliderComponent(this);
    collider->SetSize(Vector2(50 * GetScale(), 37 * GetScale()));

    rigidbody = new RigidbodyComponent(this);
    rigidbody->isKinematic = true;
}

void Player::ActorInput(const InputState& inputState) {
    velocity = Vector2::Zero;

    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) velocity.x += 10.0f;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) velocity.x -= 10.0f;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_UP)) velocity.y -= 10.0f;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_DOWN)) velocity.y += 10.0f;

    rigidbody->velocity.x += velocity.x;
    rigidbody->velocity.y += velocity.y;
}

void Player::UpdateActor(float deltaTime) {
    GetGame()->GetCamera()->Follow(this);
}
