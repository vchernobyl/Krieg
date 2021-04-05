#include "MoveComponent.h"
#include "BoxColliderComponent.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder),
      maxSpeed(0) {}

void MoveComponent::ProcessInput(const InputState& inputState) {
    input = Vector2::Zero;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT)) input.x += 1;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT)) input.x -= 1;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_UP)) input.y -= 1;
    if (inputState.Keyboard.GetKeyValue(SDL_SCANCODE_DOWN)) input.y += 1;
}

void MoveComponent::Update(float deltaTime) {
    if (auto box = owner->GetComponent<BoxColliderComponent>()) {
	auto& playerRect = box->GetCollidable();
	playerRect.velocity.x = input.x * maxSpeed * deltaTime;
	playerRect.velocity.y = input.y * maxSpeed * deltaTime;
	owner->Translate(playerRect.velocity.x, playerRect.velocity.y);
    }
}
