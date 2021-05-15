#pragma once

#include "Actor.h"

class Enemy : public Actor {
public:
    Enemy(class Game* game);
    void UpdateActor(float deltaTime) override;
    void OnCollisionEnter(const struct CollisionInfo& info) override;
    void OnTriggerEnter(const struct CollisionInfo& info) override;
private:
    struct RigidbodyComponent* rigidbody;
    class SpriteComponent* sprite;
    float velocity = -100.0f;
};
