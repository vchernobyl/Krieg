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
}

void Ship::ProcessKeyboard(const uint8_t* state) {
}
