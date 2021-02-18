#include "Ship.h"
#include "InputComponent.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game* game) : Actor(game) {
    AnimSpriteComponent* anim = new AnimSpriteComponent(this);
    std::vector<SDL_Texture*> frames = {
	game->GetTexture("assets/Ship01.png"),
	game->GetTexture("assets/Ship02.png"),
	game->GetTexture("assets/Ship03.png"),
	game->GetTexture("assets/Ship04.png"),
    };
    anim->SetAnimTextures(frames);

    InputComponent* input = new InputComponent(this);
    input->SetMaxForwardSpeed(250.0f);
    input->SetMaxAngularSpeed(2.0f);
    input->SetForwardKey(SDL_SCANCODE_UP);
    input->SetBackKey(SDL_SCANCODE_DOWN);
    input->SetClockwiseKey(SDL_SCANCODE_LEFT);
    input->SetCounterClockwiseKey(SDL_SCANCODE_RIGHT);
}

void Ship::UpdateActor(float deltaTime) {
}

void Ship::ActorInput(const uint8_t* state) {
}
