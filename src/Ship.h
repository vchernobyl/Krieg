#pragma once

#include "Actor.h"
#include "Math.h"
#include <vector>

class Ship : public Actor {
public:
    Ship(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;
private:
    class CameraMovement* cameraMovement = nullptr;
    class RigidbodyComponent* rigidbody = nullptr;
    class RocketLauncher* rocketLauncher = nullptr;

    Vector2 moveTargetPosition;
    Vector2 direction = Vector2::Right;
};
