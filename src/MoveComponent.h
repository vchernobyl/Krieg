#pragma once

#include "Component.h"

class MoveComponent : public Component {
public:
    MoveComponent(class Actor* owner, int updateOrder = 10);

    void Update(float deltaTime) override;

    float GetAngularSpeed() const { return angularSpeed; }
    void SetAngularSpeed(float speed) { angularSpeed = speed; }
    
    float GetForwardSpeed() const { return forwardSpeed; }
    void SetForwardSpeed(float speed) { forwardSpeed = speed; }

private:
    float angularSpeed;
    float forwardSpeed;
};

    
