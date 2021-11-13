#pragma once

#include "Actor.h"
#include <vector>

class Game;
class SpriteComponent;
class RigidbodyComponent;
class ParticleComponent;
class RocketLauncher;
class Damageable;

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
    void LaunchAt(Damageable* target, float speed = 12.0f);
private:
    SpriteComponent* sprite = nullptr;
    RigidbodyComponent* rb = nullptr;
    RocketLauncher* rocketLauncher = nullptr;
    ParticleComponent* trailEmitter = nullptr;

    float lifetime = 10.0f;
    int damage = 35;
};

class RocketLauncher : public Actor {
public:
    RocketLauncher(Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const InputState& inputState) override;
private:
    friend class Ship;

    bool IsTargeted(Damageable* target) const;
    void AddTarget(Damageable* target);
    void RemoveTarget(Damageable* target);

    int stacks = 3; // Equals amount of targets this weapon can have at once.
    std::vector<Damageable*> targets;
    int currentTargetIndex = 0;

    bool isActivated = false;

    float fireRate = 1.25f;
    float timeBetweenShots = 0.0f;
};
