#pragma once

#include "Component.h"
#include "Actor.h"
#include "Math.h"

class RigidbodyComponent : public Component {
public:
    RigidbodyComponent(Actor* owner, int updateOrder = 100);
    void Update(float deltaTime) override;

    void AddForce(Vector2 force) { this->force += force; }
    void ResetForce() { force = Vector2::Zero; }

    float GetMass() const { return mass; }
    void SetMass(float mass) { this->mass = mass; }

    float GetGravity() const { return gravity; }
    void SetGravity(float gravity) { this->gravity = gravity; }
private:
    Vector2 force;
    Vector2 velocity;
    Vector2 acceleration;
    float mass;
    float gravity;
};

