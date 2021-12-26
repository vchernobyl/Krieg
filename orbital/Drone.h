#pragma once

#include <Engine.h>
#include <functional>

class Drone : public Actor {
public:
    Drone(Game* game, const Vector2& movement, std::function<void()> onDestroy);
    ~Drone();
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const Contact& contact) override;
private:
    float fireRate = 1.5f;
    float fireTimer = 0.0f;

    Vector2 movement;
    std::function<void()> onDestroy;

    AudioComponent* rocketSound = nullptr;
    AudioComponent* hitSound = nullptr;
    CircleColliderComponent* collider = nullptr;
};
