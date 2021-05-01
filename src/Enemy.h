#pragma once

#include "Actor.h"

class Enemy : public Actor {
public:
    Enemy(class Game* game);
    void UpdateActor(float deltaTime) override;
    void OnCollisionEnter(const class CollisionInfo& info) override;
private:
    struct RigidbodyComponent* rigidbody;
    float velocity = -100.0f;
};
