#include "Ship.h"
#include "SpriteComponent.h"
#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"
#include "DebugRenderer.h"
#include "CameraComponent.h"
#include "Texture.h"
#include "Renderer.h"
#include "Game.h"
#include "InputSystem.h"

Ship::Ship(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this, 150);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));

    rigidbody = new RigidbodyComponent(this);
    new CircleColliderComponent(this, Vector2::Zero, 0.5f);

    camera = new CameraComponent(this);
}

void Ship::UpdateActor(float deltaTime) {
    if (Vector2::Distance(GetPosition(), targetPosition) < 0.01f) {
	rigidbody->SetVelocity(Vector2::Zero);
    } else {
	const auto movementSpeed = 250.0f;
	rigidbody->SetVelocity(direction * movementSpeed * deltaTime);
    }

    const auto rotationSpeed = 3.0f;
    const auto rotation = Math::Lerp(GetRotation(), targetRotation, rotationSpeed * deltaTime);
    if (Math::Abs(rotation - targetRotation) > 0.01f) {
	SetRotation(rotation);
    }

    DebugRenderer::DrawLine(GetPosition(), GetPosition() + GetForward(), Color::Blue);
}

void Ship::ActorInput(const InputState& inputState) {
    if (inputState.Mouse.IsButtonPressed(SDL_BUTTON_LEFT)) {
	targetPosition = camera->ScreenToWorld(inputState.Mouse.GetPosition());
	direction = Vector2::Normalize(targetPosition - GetPosition());
	targetRotation = Math::Atan2(direction.y, direction.x);
    }
}
