#pragma once

#include "Component.h"
#include "Math.h"

enum class BodyType {
    Static,
    Kinematic,
    Dynamic
};

class RigidbodyComponent : public Component {
public:
    RigidbodyComponent(class Actor* owner, BodyType type = BodyType::Dynamic);
    ~RigidbodyComponent();

    void OnUpdateWorldTransform() override;

    void SetVelocity(const Vector2& velocity);
    Vector2 GetVelocity() const;
    Vector2 GetPosition() const;

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
