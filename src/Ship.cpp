#include "Ship.h"
#include "SpriteComponent.h"
#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Targetable.h"
#include "DebugRenderer.h"
#include "CameraMovement.h"
#include "Camera.h"
#include "Texture.h"
#include "Renderer.h"
#include "Game.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "Enemy.h"
#include "RocketLauncher.h"

Ship::Ship(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));

    rigidbody = new RigidbodyComponent(this);
    auto collider = new CircleColliderComponent(this, 0.5f);
    collider->SetCollisionFilter(CollisionCategory::Player);

    cameraMovement = new CameraMovement(this);
    rocketLauncher = new RocketLauncher(game);

    SetTag("Player");
}

void Ship::UpdateActor(float deltaTime) {
    // TODO: In this case the rocket launcher is a child actor of ship. It looks like it makes sense
    // to add some sort of actor functionality, where each actor has a collection of children,
    // which will take over position and other properties of the parent.
    rocketLauncher->SetPosition(GetPosition());
    rocketLauncher->SetRotation(GetRotation());

    if (Vector2::Distance(GetPosition(), moveTargetPosition) < 0.01f) {
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
        moveTargetPosition = GetGame()->GetMainCamera()->ScreenToWorld(inputState.Mouse.GetPosition());
        direction = Vector2::Normalize(moveTargetPosition - GetPosition());
        DebugRenderer::DrawCircle(moveTargetPosition, 0.1f, Color::Red);
    }

    if (inputState.Mouse.GetButtonState(SDL_BUTTON_RIGHT) == ButtonState::Pressed) {
        auto camera = GetGame()->GetMainCamera();
        auto worldPoint = camera->ScreenToWorld(inputState.Mouse.GetPosition());
        auto physics = GetGame()->GetPhysicsWorld();

        if (auto rigidbody = physics->GetRigidbodyAt(worldPoint)) {
            if (auto targetable = rigidbody->GetOwner()->GetComponent<Targetable>()) {
                targetable->Select();
                auto owner = targetable->GetOwner();
                if (targetable->IsSelected()) {
                    rocketLauncher->AddTarget(owner);
                } else {
                    rocketLauncher->RemoveTarget(owner);
                }
            }
        }
    }
}
