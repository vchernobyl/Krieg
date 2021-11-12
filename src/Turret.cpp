#include "Turret.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "AudioComponent.h"
#include "Ship.h"

Bullet::Bullet(Game* game) : Actor(game) {
    auto texture = game->GetRenderer()->GetTexture("data/textures/Bullet.png");
    sprite = new SpriteComponent(this);
    sprite->SetTexture(texture);

    SetScale(0.35f);

    rigidbody = new RigidbodyComponent(this);
    rigidbody->SetFixedRotation(false);
    rigidbody->SetBullet(true);

    collider = new BoxColliderComponent(this, Vector2(1.0f, 0.125f) * GetScale());
    collider->SetSensor(true);
    collider->SetCollisionFilter(CollisionCategory::Bullet, CollisionCategory::Enemy |
                                 CollisionCategory::Ground);

}

void Bullet::UpdateActor(float deltaTime) {
    time += deltaTime;
    if (time >= lifeTime) {
        SetState(State::Dead);
    }
}

void Bullet::OnBeginContact(const struct Contact& contact) {
    if (dynamic_cast<Ship*>(contact.other)) return;

    SetState(State::Dead);
}

void Bullet::ShootAt(const Vector2& position) {
    auto direction = position - GetPosition();
    direction.Normalize();

    auto rotation = Math::Atan2(direction.y, direction.x);
    SetRotation(rotation);

    rigidbody->SetVelocity(direction * 24.0f);

    auto audio = new AudioComponent(this);
    audio->PlayEvent("event:/Laser_Shot");
}

Turret::Turret(Game* game) : Actor(game) {
}

void Turret::UpdateActor(float deltatime) {
}
