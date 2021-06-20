#pragma once

#include "Component.h"
#include "Math.h"

// TODO: All dependencies on Box2D should be hidden away.
#include <b2_body.h>

enum class MotionType {
    Fixed,
    GameplayDriven,
    PhysicsDriven
};

class RigidbodyComponent : public Component {
public:
    RigidbodyComponent(class Actor* owner, MotionType type = MotionType::Fixed);
    ~RigidbodyComponent();

    void SetVelocity(const Vector2& velocity);
    Vector2 GetVelocity() const;

private:
    friend class BoxColliderComponent;
    friend class PhysicsWorld;
    
    b2Body* body;
    MotionType type;
    Vector2 velocity;
};

inline void RigidbodyComponent::SetVelocity(const Vector2& velocity) {
    body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

inline Vector2 RigidbodyComponent::GetVelocity() const {
    b2Vec2 velocity = body->GetLinearVelocity();
    return Vector2(velocity.x, velocity.y);
}
