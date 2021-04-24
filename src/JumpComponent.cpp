#include "JumpComponent.h"

JumpComponent::JumpComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      position(0.0f),
      time(0.0f),
      timeToPeak(0.5f),
      maxHeight(50.0f),
      isJumping(false) {}

void JumpComponent::ProcessInput(const InputState& inputState) {
    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_UP) == Pressed) {
	// isJumping = true;
    }
}

void JumpComponent::Update(float deltaTime) {
    if (isJumping) {
	time += deltaTime;
	if (time >= timeToPeak * 2) {
	    isJumping = false;
	    time = 0.0f;
	}
	float velocity = -(2 * maxHeight) / timeToPeak;
	float gravity = (2 * maxHeight) / (timeToPeak * timeToPeak);
	float height = 0.5f * gravity * (time * time) + velocity * time + position;
	owner->SetPosition(Vector2(0, height));
    }
}
