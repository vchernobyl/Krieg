#pragma once

#include <cstdint>
#include "InputSystem.h"

class Component {
public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();
    virtual void Update(float deltaTime);
    virtual void ProcessInput(const InputState& inputState);
    int GetUpdateOrder() const { return updateOrder; }
protected:
    class Actor* owner;
    int updateOrder;
};
