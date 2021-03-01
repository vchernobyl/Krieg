#pragma once

#include "Component.h"
#include "Actor.h"
#include "InputSystem.h"

class JumpComponent : public Component {
    float velocity;
    float position;
    float time;
public:
    JumpComponent(Actor* owner, int updateOrder = 100);
    void ProcessInput(const InputState& inputState) override;
    void Update(float deltaTime) override;
    void SetInitialPosition(float y) { position = y; }
};