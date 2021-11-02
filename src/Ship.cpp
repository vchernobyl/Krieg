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
#include "PhysicsWorld.h"
#include "Enemy.h"

Rocket::Rocket(Game* game) : Actor(game) {
    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Laser.png"));

    auto collider = new CircleColliderComponent(this, 0.15f);
    collider->SetCollisionFilter(CollisionCategory::Bullet, CollisionCategory::Enemy |
                                 CollisionCategory::Ground);
    collider->SetIsSensor(true);
    rb = collider->GetAttachedRigidbody();
}

void Rocket::UpdateActor(float deltaTime) {
    lifetime -= deltaTime;
    if (lifetime <= 0.0f) {
        SetState(Actor::State::Dead);
    }
}

void Rocket::OnBeginContact(const struct Contact& contact) {
    if (!dynamic_cast<Ship*>(contact.other)) {
        SetState(Actor::State::Dead);
    }
}

void Rocket::Launch(const Vector2& direction) {
    const auto speed = 12.0f;
    rb->SetVelocity(direction * speed);
}

Ship::Ship(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));

    rigidbody = new RigidbodyComponent(this);
    auto collider = new CircleColliderComponent(this, 0.5f);
    collider->SetCollisionFilter(CollisionCategory::Player);

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

    if (inputState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed) {
        auto rocket = new Rocket(GetGame());
        rocket->SetPosition(GetPosition());
        rocket->SetRotation(GetRotation());
        rocket->Launch(direction);
    }

    if (inputState.Mouse.GetButtonState(SDL_BUTTON_RIGHT) == ButtonState::Pressed) {
        auto physics = GetGame()->GetPhysicsWorld();
        auto worldPos = camera->ScreenToWorld(inputState.Mouse.GetPosition());
        if (auto rb = physics->GetRigidbodyAt(worldPos)) {
            if (auto enemy = dynamic_cast<Enemy*>(rb->GetOwner())) {
                enemy->Select();
            }
        }
    }
}
