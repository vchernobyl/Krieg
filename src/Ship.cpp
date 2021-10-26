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

    SetTag("Player");
}

void Ship::UpdateActor(float deltaTime) {
    if (Vector2::Distance(GetPosition(), targetPosition) < 0.01f) {
	rigidbody->SetVelocity(Vector2::Zero);
    } else {
	const auto movementSpeed = 250.0f;
	rigidbody->SetVelocity(direction * movementSpeed * deltaTime);
    }

    const auto rotationSpeed = 6.0f;
    const auto step = Vector2::Lerp(GetForward(), direction, rotationSpeed * deltaTime);
    SetRotation(Math::Atan2(step.y, step.x));

    DebugRenderer::DrawLine(GetPosition(), GetPosition() + GetForward(), Color::Blue);
}

void Ship::ActorInput(const InputState& inputState) {
    if (inputState.Mouse.IsButtonPressed(SDL_BUTTON_LEFT)) {
	targetPosition = camera->ScreenToWorld(inputState.Mouse.GetPosition());
	direction = Vector2::Normalize(targetPosition - GetPosition());
	DebugRenderer::DrawCircle(targetPosition, 0.1f, Color::Red);
    }
}
