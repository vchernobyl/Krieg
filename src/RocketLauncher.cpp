#include "RocketLauncher.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "ParticleComponent.h"
#include "RigidbodyComponent.h"
#include "CircleColliderComponent.h"
#include "TargetComponent.h"
#include "HealthComponent.h"
#include "AudioComponent.h"
#include "Ship.h"
#include "Random.h"
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
    if (dynamic_cast<Ship*>(contact.other)) return;

    SetState(State::Dead);
    new Explosion(GetGame(), GetPosition());

    if (auto target = contact.other->GetComponent<HealthComponent>()) {
        target->ReceiveDamage(damage);
    }
}

void Rocket::LaunchAt(TargetComponent* target, float speed) {
    auto direction = target->GetOwner()->GetPosition() - GetPosition();
    direction.Normalize();
    
    auto rotation = Math::Atan2(direction.y, direction.x);
    SetRotation(rotation);

    rb->SetVelocity(direction * speed);

    auto audio = new AudioComponent(this);
    audio->PlayEvent("event:/Launch_Rocket");
}

RocketLauncher::RocketLauncher(Game* game) : Weapon(game) {
    fireRate = 1.25f;
    stacks = 3;
}

void RocketLauncher::UpdateActor(float deltaTime) {
    Weapon::UpdateActor(deltaTime);
    DebugRenderer::DrawCircle(GetPosition(), 0.1f, Color::Yellow);
}

void RocketLauncher::ShootAt(TargetComponent* target) {
    auto rocket = new Rocket(GetGame());
    rocket->SetPosition(GetPosition());
    rocket->LaunchAt(target);
}
