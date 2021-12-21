#pragma once

#include "Engine.h"

class Rocket : public Actor {
public:
    Rocket(Game* game);
    void UpdateActor(float deltaTime) override;
    void OnBeginContact(const Contact& contact) override;
    void Launch(const Vector2& direction);
    void SetCollisionFilter(CollisionCategory self, CollisionCategory other);
    void SetSpeed(float speed) { this->speed = speed; }
private:
    float speed = 1000.0f;
};
