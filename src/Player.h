#pragma once

#include "Actor.h"
#include "InputSystem.h"

class Bullet : public Actor {
public:
    Bullet(class Game* game);
    void OnCollisionEnter(class ColliderComponent* other) override;
private:
    class RigidbodyComponent* rigidbody;
    class BoxColliderComponent* collider;
};

class Player : public Actor {
public:
    Player(class Game* game);
    void ActorInput(const InputState& inputState) override;
    void UpdateActor(float deltaTime) override;
private:
    class RigidbodyComponent* rigidbody;
    Vector2 velocity;
};
