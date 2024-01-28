#pragma once

#include "Actor.h"

class Projectile : public Actor {
public:
    Projectile(class Game* game);
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const struct Contact& contact) override;
private:
    friend class Enemy;
    
    class RigidbodyComponent* rigidbody = nullptr;
    
    float lifeTime = 10.0f;
};

class Enemy : public Actor {
public:
    Enemy(class Game*);
    void UpdateActor(float deltaTime) override;
    void Select();
private:

    void ShootAt(const Vector2& position);

    class RigidbodyComponent* rigidbody = nullptr;
    class RocketLauncher* rocketLauncher = nullptr;

    Actor* followTarget = nullptr;
    float visionRadius = 5.0f;
    float time = 0.0f;
    float fireRate = 0.75f;
};
