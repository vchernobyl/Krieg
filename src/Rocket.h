#pragma once

#include "Actor.h"
#include <vector>

class Explosion : public Actor {
public:
    Explosion(class Game* game, const Vector2& position);
    void UpdateActor(float deltaTime) override;
private:
    float time = 0.0f;
    float lifeTime = 2.0f;
};

class Rocket : public Actor {
public:
    Rocket(class Game* game);
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const struct Contact& contact) override;
    void LaunchAt(const Actor* actor, float speed = 12.0f);
private:
    class SpriteComponent* sprite = nullptr;
    class RigidbodyComponent* rb = nullptr;
    class RocketLauncher* rocketLauncher = nullptr;
    class ParticleComponent* trailEmitter = nullptr;

    float lifetime = 10.0f;
    int damage = 35;
};

class RocketLauncher : public Actor {
public:
    RocketLauncher(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;
private:
    bool IsTargeted(const class Actor* actor) const;
    void AddTarget(const class Actor* actor);
    void RemoveTarget(const class Actor* actor);

    int stacks = 3; // Equals amount of targets this weapon can have at once.
    std::vector<const Actor*> targets;
    int currentTargetIndex = 0;

    bool isActivated = false;

    float fireRate = 1.75f;
    float timeBetweenShots = 0.0f;
};
