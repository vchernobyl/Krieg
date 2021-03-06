#pragma once

#include "HeroState.h"

class RunningState : public HeroState {
public:
    HeroState* ProcessInput(Hero& hero, const InputState& input) override;
    void Enter(Hero& hero) override;
};
