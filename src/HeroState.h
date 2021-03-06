#pragma once

#include "InputSystem.h"

class HeroState {
public:
    virtual ~HeroState() {}
    virtual void ProcessInput(class Hero& hero, const InputState& input) {}
    virtual void Update(class Hero& hero) {}
    virtual void Enter(class Hero& hero) {}
};
