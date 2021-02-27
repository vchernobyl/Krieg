#include "MovementComponent.h"

MovementComponent::MovementComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      speed(0), maxSpeed(0) {}

void MovementComponent::ProcessInput(const InputState& inputState) {
    velocity = Vector2::Zero;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) {
	velocity.x = 1;
	speed += 5;
    } else if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) {
	velocity.x = -1;
	speed += 5;
    }
    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == Released) {
	speed = 0;
    }
    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == Released) {
	speed = 0;
    }
}

void MovementComponent::Update(float deltaTime) {
    if (speed > maxSpeed) speed = maxSpeed;
    owner->TranslateX(velocity.x * speed * deltaTime);
    SDL_Log("Speed = %f", speed);
}
