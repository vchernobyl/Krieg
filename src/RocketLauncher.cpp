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

Rocket::Rocket(Game* game, RocketLauncher* rocketLauncher) : Actor(game) {
    this->rocketLauncher = rocketLauncher;
    
    sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Laser.png"));

    auto collider = new CircleColliderComponent(this, 0.15f);
    collider->SetCollisionFilter(CollisionCategory::Bullet, CollisionCategory::Enemy |
                                 CollisionCategory::Ground);
    collider->SetIsSensor(true);

    rb = collider->GetAttachedRigidbody();
    rb->SetBullet(true);

    trailEmitter = new ParticleComponent(this);
    trailEmitter->SetTexture(GetGame()->GetRenderer()->GetTexture("data/textures/Particle.png"));

    ParticleProps trailProps;
    trailProps.colorBegin = Color::White;
    trailProps.colorEnd = Vector4(0.66f, 0.66f, 0.66f, 0.0f);
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

        if (auto target = contact.other->GetComponent<Damageable>()) {
            target->Damage(damage);
            auto owner = target->GetOwner();
            if (owner->GetState() == State::Dead) {
                rocketLauncher->RemoveTarget(owner);
            }
        }
    }
}

void Rocket::LaunchAt(const Actor* actor) {
    auto direction = actor->GetPosition() - GetPosition();
    direction.Normalize();
    rb->SetVelocity(direction * 12.0f);
}

RocketLauncher::RocketLauncher(Game* game) : Actor(game) {
}

void RocketLauncher::UpdateActor(float deltaTime) {
    time += deltaTime;
    if (time >= fireRate) {
        time = 0.0f;
        for (auto target : targets) {
            auto rocket = new Rocket(GetGame(), this);
            rocket->SetPosition(GetPosition());
            rocket->LaunchAt(target);
        }
    }
}

void RocketLauncher::AddTarget(const Actor* actor) {
    targets.push_back(actor);
}

void RocketLauncher::RemoveTarget(const Actor* actor) {
    auto iter = std::find(targets.begin(), targets.end(), actor);
    if (iter != targets.end()) {
        targets.erase(iter);
    }
}
