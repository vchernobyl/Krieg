#pragma once

#include "Actor.h"
#include "Math.h"

class Rocket : public Actor {
public:
    Rocket(class Game* game);
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const struct Contact& contact) override;
    void Launch(const Vector2& direction);
private:
    class SpriteComponent* sprite;
    class RigidbodyComponent* rb;
    float lifetime = 10.0f;
};

class Ship : public Actor {
public:
    Ship(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;
private:
    class CameraMovement* cameraMovement;
    class RigidbodyComponent* rigidbody;

    Vector2 targetPosition;
    Vector2 direction = Vector2::Right;
};
