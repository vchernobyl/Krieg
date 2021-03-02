#include "JumpComponent.h"

const float MAX_HEIGHT = 75.0f;
const float PEAK_TIME = 0.5f;
const float JUMP_VELOCITY = -(2 * MAX_HEIGHT) / PEAK_TIME;
const float GRAVITY = (2 * MAX_HEIGHT) / (PEAK_TIME * PEAK_TIME);

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

    if (time >= PEAK_TIME * 2) {
	time = 0.0f;
    }

    float h = 0.5f * GRAVITY * (time * time) + JUMP_VELOCITY * time + position;
    if (h > position) h = position;
    owner->SetPositionY(h);

    SDL_Log("h = %f", h);
}
