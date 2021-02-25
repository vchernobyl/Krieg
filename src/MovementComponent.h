#pragma once

#include "Component.h"
#include "Actor.h"
#include "InputSystem.h"

class MovementComponent : public Component {
public:
    MovementComponent(Actor* owner, int updateOrder = 100);
    void ProcessInput(const InputState& inputState) override;
    void Update(float deltaTime) override;
    void SetSpeed(float speed) { this->speed = speed; }
private:
    float velocity, speed;
};

    
    
