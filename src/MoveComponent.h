#pragma once

#include "Component.h"
#include "Actor.h"
#include "InputSystem.h"
#include "Math.h"

class MoveComponent : public Component {
public:
    MoveComponent(Actor* owner, int updateOrder = 100);
    void ProcessInput(const InputState& inputState) override;
    void Update(float deltaTime) override;
    void SetMaxSpeed(float maxSpeed) { this->maxSpeed = maxSpeed; }
private:
    Vector2 input;
    Vector2 velocity;
    float maxSpeed;
};

    
    
