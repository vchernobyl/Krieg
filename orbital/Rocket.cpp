#include "Rocket.h"
#include "DamageReceiver.h"
#include <cassert>

Rocket::Rocket(Game* game, int damage) : Actor(game), damage(damage) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Laser.png"));

    auto rigidbody = new RigidbodyComponent(this);
    rigidbody->SetBullet(true);

    new CircleColliderComponent(this, 0.15f);

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
}

void Rocket::OnBeginContact(const Contact& contact) {
    SetState(Actor::State::Dead);

    if (auto receiver = contact.other->GetComponent<DamageReceiver>()) {
        receiver->ReceiveDamage(25);
    }
}

void Rocket::Launch(const Vector2& direction) {
    auto rigidbody = GetComponent<RigidbodyComponent>();
    rigidbody->SetVelocity(direction * speed * GetGame()->GetDeltaTime());
    SetRotation(Math::Atan2(direction.y, direction.x));
}

void Rocket::SetCollisionFilter(CollisionCategory self, CollisionCategory other) {
    auto collider = GetComponent<CircleColliderComponent>();
    collider->SetCollisionFilter(self, other);
}
