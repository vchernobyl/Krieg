#pragma once

#include "Actor.h"
#include "Weapon.h"
#include <vector>

class Game;
class SpriteComponent;
class RigidbodyComponent;
class ParticleComponent;
class RocketLauncher;
class TargetComponent;

struct InputState;
struct Contact;


class Explosion : public Actor {
public:
    Explosion(Game* game, const Vector2& position);
    void UpdateActor(float deltaTime) override;
private:
    float time = 0.0f;
    float lifeTime = 2.0f;
};

class Rocket : public Actor {
public:
    Rocket(Game* game);
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const Contact& contact) override;
    void LaunchAt(TargetComponent* target, float speed = 12.0f);
private:
    SpriteComponent* sprite = nullptr;
    RigidbodyComponent* rb = nullptr;
    RocketLauncher* rocketLauncher = nullptr;
    ParticleComponent* trailEmitter = nullptr;

    float lifetime = 10.0f;
    int damage = 35;
};

class RocketLauncher : public Weapon {
public:
    RocketLauncher(Game* game);
    void UpdateActor(float deltaTime) override;
    void ShootAt(TargetComponent* target) override;
    std::string GetWeaponName() const override { return "Rocket Launcher"; }
    Vector4 GetReticleColor() const override { return Color::Red; }
private:
    friend class Ship;
};
