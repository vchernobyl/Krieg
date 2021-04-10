#pragma once

#include "Component.h"
#include "InputSystem.h"
#include "Math.h"

class MoveComponent : public Component {
public:
    MoveComponent(class Actor* owner, int updateOrder = 100);
    void ProcessInput(const InputState& inputState) override;
    void SetMaxSpeed(float maxSpeed) { this->maxSpeed = maxSpeed; }
    float GetVelocity() const { return velocity.x; }
private:
    Vector2 velocity;
    float maxSpeed;
};

    
    
