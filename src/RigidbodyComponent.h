#pragma once

#include "Component.h"
#include "Math.h"

enum class MotionType {
    Static,
    Kinematic,
    Dynamic
};

class RigidbodyComponent : public Component {
public:
    RigidbodyComponent(class Actor* owner, MotionType type = MotionType::Dynamic);
    ~RigidbodyComponent();

    void SetVelocity(const Vector2& velocity);
    Vector2 GetVelocity() const;

    void ApplyForce(const Vector2& force);
    void ApplyImpulse(const Vector2& impulse);

    float GetMass() const;

    void SetGravityScale(float scale);
    void SetBullet(bool flag);

private:
    friend class CircleColliderComponent;
    friend class BoxColliderComponent;
    friend class PhysicsWorld;
    
    class b2Body* body;
    Vector2 velocity;
};
