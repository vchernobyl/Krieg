#pragma once

#include "HeroState.h"

class IdleState : public HeroState {
public:
    void ProcessInput(Hero& hero, const InputState& input) override;
    void Enter(Hero& hero) override;
};
