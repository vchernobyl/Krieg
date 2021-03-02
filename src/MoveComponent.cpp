#include "MoveComponent.h"

// TODO: Currently the lerping from current velocity to the
// target velocity is done linearly. Take a look if this component
// can be juiced up by introducing some sort of acceleration or
// time to reach the maximum speed.
MoveComponent::MoveComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      maxSpeed(0) {}

void MoveComponent::ProcessInput(const InputState& inputState) {
    input.x = 0;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) input.x += 1;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) input.x -= 1;
}

void MoveComponent::Update(float deltaTime) {
    float target = maxSpeed * input.x;
    float t = 4.0f * deltaTime;
    velocity.x = Math::Lerp(velocity.x, target, t);
    owner->TranslateX(velocity.x * deltaTime);
}
