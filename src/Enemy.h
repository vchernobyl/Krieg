#pragma once

#include "Actor.h"

class Enemy : public Actor {
public:
    Enemy(class Game*);
    void UpdateActor(float deltaTime) override;
private:
    class RigidbodyComponent* rigidbody = nullptr;
    Actor* followTarget = nullptr;
};
