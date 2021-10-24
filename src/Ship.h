#pragma once

#include "Actor.h"
#include "Math.h"

class Ship : public Actor {
public:
    Ship(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;

private:
    class CameraComponent* camera;
    class RigidbodyComponent* rigidbody;
    Vector2 targetPosition;
    Vector2 direction;
    float targetRotation;
};
