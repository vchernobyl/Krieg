#include "JumpComponent.h"

const float JUMP_VELOCITY = -15.0f;
const float GRAVITY = 8.0f;

JumpComponent::JumpComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      velocity(0),
      position(0),
      time(0) {}

void JumpComponent::ProcessInput(const InputState& inputState) {
    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed) {
	velocity = JUMP_VELOCITY;
    }
}

void JumpComponent::Update(float deltaTime) {
    time += deltaTime;
    float h = 0.5f * GRAVITY * (time * time) + JUMP_VELOCITY * time + position;
    SDL_Log("h = %f", h);
}
