#pragma once

#include "Component.h"
#include "Math.h"

// TODO: All dependencies on Box2D should be hidden away.
#include <b2_body.h>

enum class MotionType {
    Fixed,
    GameDriven,
    PhysicsDriven
};

class RigidbodyComponent : public Component {
public:
    Vector2 velocity;

    RigidbodyComponent(class Actor* owner);
    ~RigidbodyComponent();

    void SetMotionType(MotionType motionType);
    const MotionType& GetMotionType() const;
private:
    MotionType motionType;
    b2Body* body;
};

inline void RigidbodyComponent::SetMotionType(MotionType type) {
    this->motionType = type;
}

inline const MotionType& RigidbodyComponent::GetMotionType() const {
    return motionType;
}
