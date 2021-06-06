#pragma once

#include "Component.h"
#include "Math.h"

enum class MotionType {
    Fixed,
    GameDriven,
    PhysicsDriven
};

class RigidbodyComponent : public Component {
public:
    RigidbodyComponent(class Actor* owner);
    ~RigidbodyComponent();

    Vector2 velocity;

    void SetMotionType(MotionType motionType) { this->motionType = motionType; }
    const MotionType& GetMotionType() const { return motionType; }
private:
    MotionType motionType;
};
