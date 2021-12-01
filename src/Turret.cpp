#include "Turret.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "AudioComponent.h"
#include "Ship.h"
#include "TargetComponent.h"
#include "InputSystem.h"
#include "Camera.h"
#include "PhysicsWorld.h"
#include "DebugRenderer.h"
#include "HealthComponent.h"

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

    if (auto target = contact.other->GetComponent<HealthComponent>()) {
        target->ReceiveDamage(damage);
    }
}

void Bullet::ShootAt(const Vector2& position, float speed) {
    auto direction = position - GetPosition();
    direction.Normalize();

    auto rotation = Math::Atan2(direction.y, direction.x);
    SetRotation(rotation);

    rigidbody->SetVelocity(direction * speed);

    auto audio = new AudioComponent(this);
    audio->PlayEvent("event:/Laser_Shot");
}

Turret::Turret(Game* game) : Weapon(game) {
    fireRate = 6.5f;
    stacks = 2;
}

void Turret::UpdateActor(float deltaTime) {
    Weapon::UpdateActor(deltaTime);
    DebugRenderer::DrawCircle(GetPosition(), 0.1f, Color::Red);
}

void Turret::ShootAt(TargetComponent* target) {
    auto bullet = new Bullet(GetGame());
    bullet->SetPosition(GetPosition());
    bullet->ShootAt(target->GetOwner()->GetPosition());
}
