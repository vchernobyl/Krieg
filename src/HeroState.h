#pragma once

#include "InputSystem.h"

class HeroState {
public:
    virtual ~HeroState() {}
    virtual HeroState* ProcessInput(class Hero& hero, const InputState& input) = 0;
    virtual void Update(class Hero& hero) {}
    virtual void Enter(class Hero& hero) {}
};
