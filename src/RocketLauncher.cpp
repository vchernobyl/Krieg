#include "RocketLauncher.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "ParticleComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "RigidbodyComponent.h"
#include "CircleColliderComponent.h"
#include "Ship.h"
#include "Damageable.h"
#include "Random.h"
#include "AudioComponent.h"
#include "InputSystem.h"
#include "Camera.h"
#include "PhysicsWorld.h"
#include "DebugRenderer.h"

Explosion::Explosion(Game* game, const Vector2& position) : Actor(game) {
    SetPosition(position);

    auto emitter = new ParticleComponent(this);
    auto texture = game->GetRenderer()->GetTexture("data/textures/Particle.png");
    emitter->SetTexture(texture);

    ParticleProps props;
    props.velocity = Random::GetVector(Vector2(-1.0f, -1.0f), Vector2(1.0f, 1.0f));
    props.velocityVariation = Vector2(-1.0f, 1.0f);
    props.colorBegin = Color::Red;
    props.colorEnd = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
    props.sizeBegin = 0.15f;
    props.sizeEnd = 0.0f;
    props.sizeVariation = 0.0f;
    props.rotationBegin = 0.0f;
    props.rotationSpeed = 2.0f;
    props.lifeTime = lifeTime;

    emitter->Emit(props, 15);

    auto audio = new AudioComponent(this);
    audio->PlayEvent("event:/Rocket_Explosion");
}

void Explosion::UpdateActor(float deltaTime) {
    time += deltaTime;
    if (time >= lifeTime) {
        SetState(State::Dead);
    }
}

Rocket::Rocket(Game* game) : Actor(game) {
    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Laser.png"));

    auto collider = new CircleColliderComponent(this, 0.15f);
    collider->SetCollisionFilter(CollisionCategory::Bullet, CollisionCategory::Enemy |
                                 CollisionCategory::Ground);
    collider->SetSensor(true);

    rb = collider->GetAttachedRigidbody();
    rb->SetBullet(true);

    trailEmitter = new ParticleComponent(this, sprite->GetDrawOrder() - 1);
    trailEmitter->SetTexture(GetGame()->GetRenderer()->GetTexture("data/textures/Particle.png"));

    ParticleProps trailProps;
    trailProps.colorBegin = Color::Red;
    trailProps.colorEnd = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
    trailProps.sizeBegin = Random::GetFloatRange(0.10f, 0.15f);
    trailProps.sizeEnd = 0.0f;
    trailProps.rotationBegin = 0.0f;
    trailProps.rotationSpeed = Random::GetFloatRange(0.35f, 2.2f);
    trailProps.lifeTime = 0.55f;

    trailEmitter->SetProps(trailProps);
    trailEmitter->SetEmissionRate(45.0f);
    trailEmitter->Start();
}

void Rocket::UpdateActor(float deltaTime) {
    lifetime -= deltaTime;
    if (lifetime <= 0.0f) {
        SetState(State::Dead);
    }
}

void Rocket::OnBeginContact(const Contact& contact) {
    if (!dynamic_cast<Ship*>(contact.other)) {
        SetState(State::Dead);

        new Explosion(GetGame(), GetPosition());

        if (auto target = contact.other->GetComponent<Damageable>()) {
            target->Damage(damage);
        }
    }
}

void Rocket::LaunchAt(const Actor* actor, float speed) {
    auto direction = actor->GetPosition() - GetPosition();
    direction.Normalize();
    rb->SetVelocity(direction * speed);

    auto audio = new AudioComponent(this);
    audio->PlayEvent("event:/Launch_Rocket");
}

RocketLauncher::RocketLauncher(Game* game) : Actor(game) {
}

void RocketLauncher::UpdateActor(float deltaTime) {
    DebugRenderer::DrawCircle(GetPosition(), 0.1f, Color::Yellow);

    timeBetweenShots += deltaTime;

    if (targets.empty()) return;

    if (timeBetweenShots >= 1.0f / fireRate) {
        timeBetweenShots = 0.0f;
        auto rocket = new Rocket(GetGame());
        rocket->SetPosition(GetPosition());
        rocket->LaunchAt(targets[currentTargetIndex]);
        currentTargetIndex = (currentTargetIndex + 1) % targets.size();
    }
}

void RocketLauncher::ActorInput(const InputState& inputState) {
    if (inputState.Mouse.GetButtonState(SDL_BUTTON_RIGHT) == ButtonState::Pressed) {
        auto camera = GetGame()->GetMainCamera();
        auto worldPoint = camera->ScreenToWorld(inputState.Mouse.GetPosition());
        auto physics = GetGame()->GetPhysicsWorld();

        if (auto rigidbody = physics->GetRigidbodyAt(worldPoint)) {
            if (auto target = rigidbody->GetOwner()->GetComponent<Damageable>()) {
                auto actor = target->GetOwner();
                if (IsTargeted(actor)) {
                    target->Deselect();
                    RemoveTarget(actor);
                } else if (targets.size() < stacks) {
                    target->Select();
                    AddTarget(actor);
                    target->SetOnDestroy([this](const Actor* actor) { RemoveTarget(actor); });
                }
            }
        }
    }
}

void RocketLauncher::AddTarget(const Actor* actor) {
    auto iter = std::find(targets.begin(), targets.end(), actor);
    if (iter == targets.end()) {
        targets.push_back(actor);
    }
}

void RocketLauncher::RemoveTarget(const Actor* actor) {
    auto iter = std::find(targets.begin(), targets.end(), actor);
    if (iter != targets.end()) {
        targets.erase(iter);
    }
}

bool RocketLauncher::IsTargeted(const Actor* actor) const {
    auto iter = std::find(targets.begin(), targets.end(), actor);
    return iter != targets.end();
}
