#pragma once

#include "Engine.h"

class Rocket : public Actor {
public:
    Rocket(Game* game, int damage = 30);
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const Contact& contact) override;
    void Launch(const Vector2& direction);
    void SetSpeed(float speed) { this->speed = speed; }
private:
    float speed = 100.0f;
    int damage;

    ParticleComponent* trailEmitter = nullptr;
    CircleColliderComponent* collider = nullptr;
};
