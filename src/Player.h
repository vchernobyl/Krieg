#pragma once

#include "Actor.h"

class ColliderComponent;
class BoxColliderComponent;
class RigidbodyComponent;
class SpriteComponent;
class InputSystem;

class Bullet : public Actor {
public:
    Bullet(Game* game, const Vector2& direction);
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
    SpriteComponent* sprite;
    Vector2 velocity;
    Vector2 direction;
    bool isJumping = false;
};
