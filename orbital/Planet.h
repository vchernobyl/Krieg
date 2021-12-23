#pragma once

#include <Engine.h>

class Planet : public Actor {
public:
    Planet(Game* game, const Vector2& center, float radius);
    void UpdateActor(float deltaTime) override;

    const Vector2& GetCenter() { return center; }
    float GetRadius() const { return radius; }
    void SetRadius(float radius) { this->radius = radius; }

private:
    Vector2 center;
    float radius;

    float fireRate = 1.0f;
    float time = 0.0f;

    int maxDrones = 5;
    int droneCount = 0;
    float droneSpawnInterval = 2.0f; // In seconds.
    float droneSpawnTime = 0.0f;

    AudioComponent* rocketSound = nullptr;
};
