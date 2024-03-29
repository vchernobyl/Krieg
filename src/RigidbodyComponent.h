#pragma once

#include "Component.h"
#include "Maths.h"

enum class BodyType {
    Static,
    Kinematic,
    Dynamic
};

class RigidbodyComponent : public Component {
public:
    RigidbodyComponent(class Actor* owner, BodyType type = BodyType::Dynamic);
    ~RigidbodyComponent();

    void SetVelocity(const Vector2& velocity);
    Vector2 GetVelocity() const;

    void SetPosition(const Vector2& position);
    Vector2 GetPosition() const;

    float GetAngle() const;
    void SetAngle(float angle);

    void ApplyForce(const Vector2& force);
    void ApplyImpulse(const Vector2& impulse);

    float GetMass() const;

    void SetGravityScale(float scale);
    void SetBullet(bool flag);
    void SetFixedRotation(bool flag);

private:
    friend class CircleColliderComponent;
    friend class BoxColliderComponent;
    friend class PhysicsWorld;
    
    class b2Body* body;
};
