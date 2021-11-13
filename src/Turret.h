#pragma once

#include "Actor.h"
#include <vector>

class Game;
class SpriteComponent;
class BoxColliderComponent;
class RigidbodyComponent;
class Damageable;

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

class Turret : public Actor {
public:
    Turret(Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;
private:
    friend class Ship;
    
    bool IsTargeted(Damageable* target) const;
    void AddTarget(Damageable* target);
    void RemoveTarget(Damageable* target);

    float fireRate = 6.0f;
    float timeBetweenShots = 0.0f;
    
    int stacks = 2;
    int currentTargetIndex = 0;

    bool isActivated = false;

    std::vector<Damageable*> targets;
};
