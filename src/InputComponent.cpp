#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner) :
    MoveComponent(owner),
    forwardKey(0), backKey(0),
    clockwiseKey(0), counterClockwiseKey(0) {}

void InputComponent::ProcessInput(const uint8_t* keyState) {
    float forwardSpeed = 0.0f;
    if (keyState[forwardKey]) forwardSpeed += maxForwardSpeed;
    if (keyState[backKey]) forwardSpeed -= maxForwardSpeed;
    SetForwardSpeed(forwardSpeed);

    float angularSpeed = 0.0f;
    if (keyState[clockwiseKey]) angularSpeed += maxAngularSpeed;
    if (keyState[counterClockwiseKey]) angularSpeed -= maxAngularSpeed;
    SetAngularSpeed(angularSpeed);
}
