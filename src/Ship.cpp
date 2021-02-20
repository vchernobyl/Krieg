#include "Ship.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "Game.h"

Ship::Ship(Game* game) : Actor(game) {
    SpriteComponent* sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetTexture("assets/Ship.png"));

    InputComponent* input = new InputComponent(this);
    input->SetForwardKey(SDL_SCANCODE_UP);
    input->SetBackKey(SDL_SCANCODE_DOWN);
    input->SetClockwiseKey(SDL_SCANCODE_LEFT);
    input->SetCounterClockwiseKey(SDL_SCANCODE_RIGHT);
    input->SetMaxForwardSpeed(300.0f);
    input->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime) {
}

void Ship::ActorInput(const uint8_t* state) {
}
