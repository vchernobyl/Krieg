#pragma once

#include "Actor.h"

class Enemy : public Actor {
public:
    Enemy(class Game* game);
    void UpdateActor(float deltaTime) override;
private:
    struct RigidbodyComponent* rigidbody;

    float time = 0.0f;
    float velocity = -100.0f;
};
