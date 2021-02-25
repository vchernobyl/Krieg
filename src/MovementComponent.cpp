#include "MovementComponent.h"

MovementComponent::MovementComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {}

void MovementComponent::ProcessInput(const InputState& inputState) {
    velocity = 0;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) velocity += 1;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) velocity -= 1;
}

void MovementComponent::Update(float deltaTime) {
    float x = owner->GetPosition().x + (velocity * speed * deltaTime);
    float y = owner->GetPosition().y;
    owner->SetPosition(Vector2(x, y));
}
