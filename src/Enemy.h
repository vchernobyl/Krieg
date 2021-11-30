#pragma once

#include "Actor.h"

class Enemy : public Actor {
public:
    Enemy(class Game*);
    void UpdateActor(float deltaTime) override;
    void Select();
private:
    class RigidbodyComponent* rigidbody = nullptr;
    class RocketLauncher* rocketLauncher = nullptr;

    Actor* followTarget = nullptr;
    float visionRadius = 5.0f;
};
