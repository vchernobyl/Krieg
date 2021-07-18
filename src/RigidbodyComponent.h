#pragma once

#include "Component.h"
#include "Math.h"

enum class MotionType {
    Fixed,
    GameplayDriven,
    PhysicsDriven
};

class RigidbodyComponent : public Component {
public:
    RigidbodyComponent(class Actor* owner, MotionType type = MotionType::PhysicsDriven);
    ~RigidbodyComponent();

    void SetVelocity(const Vector2& velocity);
    Vector2 GetVelocity() const;

    void ApplyForce(const Vector2& force);

private:
    friend class BoxColliderComponent;
    friend class PhysicsWorld;
    
    class b2Body* body;
    MotionType type;
    Vector2 velocity;
};
