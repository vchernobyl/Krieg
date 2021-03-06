#pragma once

#include "HeroState.h"
#include "MoveComponent.h"
#include "JumpComponent.h"

class IdleState : public HeroState {
public:
    HeroState* Update(Hero& hero) override;
    void Enter(Hero& hero) override;
private:
    MoveComponent* move;
    JumpComponent* jump;
};
