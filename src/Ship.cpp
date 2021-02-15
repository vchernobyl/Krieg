#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game* game)
    : Actor(game),
      rightSpeed(0.0f),
      downSpeed(0.0f) {
    AnimSpriteComponent* anim = new AnimSpriteComponent(this);
    std::vector<SDL_Texture*> frames = {
	game->GetTexture("assets/Ship01.png"),
	game->GetTexture("assets/Ship02.png"),
	game->GetTexture("assets/Ship03.png"),
	game->GetTexture("assets/Ship04.png"),
    };
    anim->SetAnimTextures(frames);
}

void Ship::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);
    Vector2 pos = GetPosition();
    pos.x += rightSpeed * deltaTime;
    pos.y += downSpeed * deltaTime;
    SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t* state) {
    rightSpeed = 0.0f;
    downSpeed = 0.0f;
    if (state[SDL_SCANCODE_D]) rightSpeed += 250.0f;
    if (state[SDL_SCANCODE_A]) rightSpeed -= 250.0f;
    if (state[SDL_SCANCODE_S]) downSpeed += 300.0f;
    if (state[SDL_SCANCODE_W]) downSpeed -= 300.0f;
}
