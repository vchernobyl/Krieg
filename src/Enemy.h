#pragma once

#include "Actor.h"
#include "InputSystem.h"
#include "Math.h"

class Enemy : public Actor {
public:
    Enemy(class Game* game);
    void ActorInput(const InputState& input) override;
    void UpdateActor(float deltaTime) override;
private:
    Vector2 velocity;
    struct RigidbodyComponent* rigidbody;
};
