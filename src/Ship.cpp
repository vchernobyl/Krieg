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

    if (inputState.Mouse.IsButtonPressed(SDL_BUTTON_LEFT)) {
	SDL_Log("left");
    }
    if (inputState.Mouse.IsButtonPressed(SDL_BUTTON_RIGHT)) {
	SDL_Log("right");
    }
    if (inputState.Mouse.IsButtonPressed(SDL_BUTTON_MIDDLE)) {
	SDL_Log("middle");
    }

    auto pos = inputState.Mouse.GetPosition();
    auto world = GetGame()->GetRenderer()->ScreenToWorld(pos);
    SDL_Log("screen.x=%f, screen.y=%f, world.x=%f, world.y=%f", pos.x, pos.y, world.x, world.y);

    auto scroll = inputState.Mouse.GetScrollWheel();
    if (scroll != Vector2::Zero) {
	SDL_Log("x=%f, y=%f", scroll.x, scroll.y);
    }
    
    SetRotation(rotation);
    SetPosition(position);
}
