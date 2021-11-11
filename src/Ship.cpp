#include "Ship.h"
#include "SpriteComponent.h"
#include "CircleColliderComponent.h"
#include "RigidbodyComponent.h"
#include "DebugRenderer.h"
#include "CameraMovement.h"
#include "Camera.h"
#include "Texture.h"
#include "Renderer.h"
#include "Game.h"
#include "InputSystem.h"
#include "ParticleComponent.h"
#include "Random.h"
#include "Rocket.h"

Ship::Ship(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Ship.png"));

    rigidbody = new RigidbodyComponent(this);
    auto collider = new CircleColliderComponent(this, 0.5f);
    collider->SetCollisionFilter(CollisionCategory::Player);

    new CameraMovement(this);
    
    trailEmitter = new ParticleComponent(this, sprite->GetDrawOrder() - 1);
    trailEmitter->SetTexture(game->GetRenderer()->GetTexture("data/textures/Particle.png"));

    ParticleProps trailProps;
    trailProps.velocity = Vector2::Zero;
    trailProps.colorBegin = Color::White;
    trailProps.colorEnd = Vector4(0.66f, 0.66f, 0.66f, 0.0f);
    trailProps.sizeBegin = Random::GetFloatRange(0.15f, 0.25f);
    trailProps.sizeEnd = 0.0f;
    trailProps.sizeVariation = 0.1f;
    trailProps.rotationBegin = 0.0f;
    trailProps.rotationSpeed = Random::GetFloatRange(0.35f, 2.2f);
    trailProps.lifeTime = 1.25f;

    trailEmitter->SetEmissionRate(15.0f);
    trailEmitter->SetProps(trailProps);

    rocketLauncher = new RocketLauncher(game);

    SetTag("Player");
}

void Ship::UpdateActor(float deltaTime) {
    rocketLauncher->SetPosition(GetPosition());
    rocketLauncher->SetRotation(GetRotation());

    if (Vector2::Distance(GetPosition(), moveTargetPosition) < 0.01f) {
        rigidbody->SetVelocity(Vector2::Zero);
        trailEmitter->Stop();
    } else {
        const auto movementSpeed = 250.0f;
        rigidbody->SetVelocity(direction * movementSpeed * deltaTime);
        trailEmitter->Start();
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
}
