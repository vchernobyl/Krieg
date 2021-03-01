#include "MoveComponent.h"

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
