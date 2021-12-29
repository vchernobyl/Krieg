#pragma once

#include <Engine.h>

class Drone : public Actor {
public:
    Drone(Game* game, const Vector2& movement);
    ~Drone();
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const Contact& contact) override;
private:

    Vector2 movement;

    AudioComponent* rocketSound = nullptr;
    AudioComponent* hitSound = nullptr;
    CircleColliderComponent* collider = nullptr;
};
