#include "Player.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"

Player::Player(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetTexture("assets/adventurer-idle-00.png"));
    
    SetPosition(Vector2(300, 150));
    SetScale(1.5f);
    
    auto collider = new BoxColliderComponent(this);
    collider->SetCollidable( { 0, 0, 50 * GetScale(), 37 * GetScale() });
}

void Player::ActorInput(const InputState& inputState) {
    velocity = Vector2::Zero;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) velocity.x += 10.0f;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) velocity.x -= 10.0f;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_UP)) velocity.y -= 10.0f;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_DOWN)) velocity.y += 10.0f;
}

void Player::UpdateActor(float deltaTime) {
    if (auto box = GetComponent<BoxColliderComponent>()) {
	auto& playerRect = box->GetCollidable();
	playerRect.velocity.x += velocity.x;
	playerRect.velocity.y += velocity.y;
	Translate(playerRect.velocity.x * deltaTime, playerRect.velocity.y * deltaTime);
    }
}
