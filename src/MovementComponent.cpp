#include "MovementComponent.h"

MovementComponent::MovementComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {}

void MovementComponent::ProcessInput(const uint8_t* keyState) {
    if (keyState[SDL_SCANCODE_RIGHT]) velocity += 1;
    if (keyState[SDL_SCANCODE_LEFT]) velocity -= 1;
}

void MovementComponent::Update(float deltaTime) {
    float x = owner->GetPosition().x + (velocity * speed * deltaTime);
    float y = owner->GetPosition().y;
    owner->SetPosition(Vector2(x, y));
    velocity = 0;
}

