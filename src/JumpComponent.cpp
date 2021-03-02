#include "JumpComponent.h"

const float MAX_HEIGHT = 75.0f;
const float PEAK_TIME = 0.5f;
const float JUMP_VELOCITY = -(2 * MAX_HEIGHT) / PEAK_TIME;
const float GRAVITY = (2 * MAX_HEIGHT) / (PEAK_TIME * PEAK_TIME);

JumpComponent::JumpComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      position(0),
      time(0),
      isJumping(false) {}

void JumpComponent::ProcessInput(const InputState& inputState) {
    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed) {
	isJumping = true;
    }
}

void JumpComponent::Update(float deltaTime) {
    if (isJumping) {
	time += deltaTime;
	if (time >= PEAK_TIME * 2) {
	    isJumping = false;
	    time = 0.0f;
	}
	float h = 0.5f * GRAVITY * (time * time) + JUMP_VELOCITY * time + position;
	owner->SetPositionY(h);
    }
}
