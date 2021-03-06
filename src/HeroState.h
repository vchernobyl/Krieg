#pragma once

#include "InputSystem.h"

class HeroState {
public:
    virtual ~HeroState() {}
    virtual HeroState* ProcessInput(class Hero& hero, const InputState& input) { return nullptr; }
    virtual HeroState* Update(class Hero& hero) { return nullptr; }
    virtual void Enter(class Hero& hero) {}
};
