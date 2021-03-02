#pragma once

#include "Component.h"
#include "Actor.h"
#include "InputSystem.h"

class JumpComponent : public Component {
public:
    JumpComponent(Actor* owner, int updateOrder = 100);
    void ProcessInput(const InputState& inputState) override;
    void Update(float deltaTime) override;
    void SetInitialPosition(float y) { position = y; }
    void SetTimeToPeak(float time) { timeToPeak = time; }
    void SetMaxHeight(float height) { maxHeight = height; }
private:
    float position;
    float time;
    float timeToPeak;
    float maxHeight;
    bool isJumping;
};
