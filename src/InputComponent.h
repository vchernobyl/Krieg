#pragma once

#include "MoveComponent.h"

class InputComponent : public MoveComponent {
public:
    InputComponent(class Actor* owner);
    void ProcessInput(const uint8_t* keyState) override;

    float GetMaxForwardSpeed() const { return maxForwardSpeed; }
    void SetMaxForwardSpeed(float speed) { maxForwardSpeed = speed; }

    float GetMaxAngularSpeed() const { return maxAngularSpeed; }
    void SetMaxAngularSpeed(float speed) { maxAngularSpeed = speed; }

    int GetForwardKey() const { return forwardKey; }
    void SetForwardKey(int key) { forwardKey = key; }

    int GetBackKey() const { return backKey; }
    void SetBackKey(int key) { backKey = key; }

    int GetClockwiseKey() const { return clockwiseKey; }
    void SetClockwiseKey(int key) { clockwiseKey = key; }

    int GetCounterClockwiseKey() const { return counterClockwiseKey; }
    void SetCounterClockwiseKey(int key) { counterClockwiseKey = key; }

private:
    float maxForwardSpeed, maxAngularSpeed;
    int forwardKey, backKey;
    int clockwiseKey, counterClockwiseKey;
};
