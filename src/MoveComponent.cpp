#include "MoveComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      maxSpeed(0) {}

void MoveComponent::ProcessInput(const InputState& inputState) {
    velocity = Vector2::Zero;

    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) velocity.x = maxSpeed;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) velocity.x = -maxSpeed;
    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_UP) == Pressed) velocity.y = -350.0f;
    
}

void MoveComponent::Update(float deltaTime) {
    auto rigidbody = owner->GetComponent<RigidbodyComponent>();
    rigidbody->velocity.x = velocity.x * deltaTime;
    rigidbody->velocity.y += velocity.y * deltaTime;
}
