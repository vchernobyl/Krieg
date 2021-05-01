#pragma once

#include "Actor.h"

class ColliderComponent;
class RigidbodyComponent;
class BoxColliderComponent;
class InputSystem;

class Bullet : public Actor {
public:
    Bullet(Game* game);
    void OnCollisionEnter(const CollisionInfo& info) override;
private:
    RigidbodyComponent* rigidbody;
    BoxColliderComponent* collider;
};

class Player : public Actor {
public:
    Player(Game* game);
    void ActorInput(const InputState& inputState) override;
    void UpdateActor(float deltaTime) override;
private:
    RigidbodyComponent* rigidbody;
    Vector2 velocity;
    bool isJumping = false;
};
