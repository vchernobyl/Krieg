#include "Ship.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Texture.h"
#include "Renderer.h"
#include "Game.h"
#include "InputSystem.h"

Ship::Ship(Game* game) : Actor(game), laserCooldown(0.0f) {
    SpriteComponent* sprite = new SpriteComponent(this, 150);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));

    rigidbody = new RigidbodyComponent(this, MotionType::Kinematic);

    new BoxColliderComponent(this, Vector2(1.0f, 1.0f));
    new MoveComponent(this);
}

void Ship::UpdateActor(float deltaTime) {
    laserCooldown -= deltaTime;
}

void Ship::ActorInput(const InputState& inputState) {
    Vector2 position = GetPosition();
    float rotation = GetRotation();

    const float speed = 3.5f;
    const float rotationSpeed = 0.1f;

    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) {
	rotation += rotationSpeed;
    }
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) {
	rotation -= rotationSpeed;
    }
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_UP)) {
	rigidbody->SetVelocity(GetForward() * speed);
    } else {
	rigidbody->SetVelocity(Vector2(0.0f, 0.0f));
    }
    
    SetRotation(rotation);
    SetPosition(position);
}
