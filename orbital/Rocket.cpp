#include "Rocket.h"

Rocket::Rocket(Game* game) : Actor(game) {
    auto sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetRenderer()->GetTexture("data/textures/Laser.png"));

    auto rigidbody = new RigidbodyComponent(this);
    rigidbody->SetBullet(true);

    new CircleColliderComponent(this, 0.15f);
}

void Rocket::UpdateActor(float deltaTime) {
}

void Rocket::OnBeginContact(const Contact& contact) {
    SetState(Actor::State::Dead);
}

void Rocket::Launch(const Vector2& direction) {
    auto rigidbody = GetComponent<RigidbodyComponent>();
    rigidbody->SetVelocity(direction * speed * GetGame()->GetDeltaTime());
}

void Rocket::SetCollisionFilter(CollisionCategory self, CollisionCategory other) {
    auto collider = GetComponent<CircleColliderComponent>();
    collider->SetCollisionFilter(self, other);
}
