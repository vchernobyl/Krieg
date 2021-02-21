#include "Ship.h"
#include "Laser.h"
#include "Game.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"

Ship::Ship(Game* game)
    : Actor(game),
      laserCooldown(0.0f) {
    SpriteComponent* sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetTexture("assets/Ship.png"));

    RigidbodyComponent* rigidbody = new RigidbodyComponent(this);
    rigidbody->SetMass(0.5f);
    rigidbody->SetGravity(9.82f * 10);

    InputComponent* input = new InputComponent(this);
    input->SetForwardKey(SDL_SCANCODE_UP);
    input->SetBackKey(SDL_SCANCODE_DOWN);
    input->SetClockwiseKey(SDL_SCANCODE_LEFT);
    input->SetCounterClockwiseKey(SDL_SCANCODE_RIGHT);
    input->SetMaxForwardSpeed(300.0f);
    input->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime) {
    laserCooldown -= deltaTime;
}

void Ship::ActorInput(const uint8_t* keyState) {
    if (keyState[SDL_SCANCODE_SPACE] && laserCooldown <= 0.0f) {
	Laser* laser = new Laser(GetGame());
	laser->SetPosition(GetPosition());
	laser->SetRotation(GetRotation());
	laserCooldown = 0.5f;
    }
}
