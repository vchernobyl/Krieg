#include "JumpComponent.h"

// TODO: Think about saner defaults here.
// It probably makes sense to set position to owners position.
// Also some defaults for time to peak and max height probably
// make sense in this case.
JumpComponent::JumpComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      position(0.0f),
      time(0.0f),
      timeToPeak(0.0f),
      maxHeight(0.0f),
      isJumping(false) {}

void JumpComponent::ProcessInput(const InputState& inputState) {
    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed) {
	isJumping = true;
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
	owner->SetPositionY(height);
    }
}
