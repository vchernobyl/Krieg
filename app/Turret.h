#pragma once

#include "Actor.h"
#include "Weapon.h"
#include <vector>

class Game;
class SpriteComponent;
class BoxColliderComponent;
class RigidbodyComponent;
class TargetComponent;
class ParticleComponent;

class HitParticles : public Actor {
public:
    HitParticles(Game* game, const Vector2& position);
    void UpdateActor(float deltaTime) override;
private:
    ParticleComponent* particles = nullptr;
    float time = 0.0f;
    float lifeTime = 0.5f;
};

class Bullet : public Actor {
public:
    Bullet(Game* game);
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const struct Contact& contact) override;
    void ShootAt(const Vector2& position, float speed = 18.0f);
private:
    SpriteComponent* sprite = nullptr;
    BoxColliderComponent* collider = nullptr;
    RigidbodyComponent* rigidbody = nullptr;

    float lifeTime = 5.0f;
    float time = 0.0f;

    int damage = 10;
};

class Turret : public Weapon {
public:
    Turret(Game* game);
    void UpdateActor(float deltaTime) override;
    void ShootAt(TargetComponent* target) override;
    std::string GetWeaponName() const override { return "Turret"; }
    Vector4 GetReticleColor() const override { return Color::Cyan; }
private:
    friend class Ship;
};
