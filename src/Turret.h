#pragma once

#include "Actor.h"
#include <vector>

class Game;
class SpriteComponent;
class BoxColliderComponent;
class RigidbodyComponent;

class Bullet : public Actor {
public:
    Bullet(Game* game);
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const struct Contact& contact) override;
    void ShootAt(const Vector2& position);
private:
    SpriteComponent* sprite = nullptr;
    BoxColliderComponent* collider = nullptr;
    RigidbodyComponent* rigidbody = nullptr;

    float lifeTime = 5.0f;
    float time = 0.0f;
};

class Turret : public Actor {
public:
    Turret(Game* game);
    void UpdateActor(float deltaTime) override;
private:
    float fireRate = 8.0f;
    float timeBetweenShots = 0.0f;

    std::vector<const Actor*> targets;
};
