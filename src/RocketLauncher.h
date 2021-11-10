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
    Rocket(class Game* game, class RocketLauncher* rocketLauncher);
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const struct Contact& contact) override;
    void LaunchAt(const Actor* actor);
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
    void AddTarget(const Actor* actor);
    void RemoveTarget(const Actor* actor);
private:
    float fireRate = 0.75f; // Shots per second.
    float time = 0.0f;
    
    std::vector<const Actor*> targets;
};
