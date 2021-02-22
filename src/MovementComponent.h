#pragma once

#include "Component.h"
#include "Actor.h"

class MovementComponent : public Component {
public:
    MovementComponent(Actor* owner, int updateOrder = 100);
    void ProcessInput(const uint8_t* keyState) override;
    void Update(float deltaTime) override;
    void SetSpeed(float speed) { this->speed = speed; }
private:
    float velocity, speed;
};

    
    
