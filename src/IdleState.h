#pragma once

#include "HeroState.h"
#include "MoveComponent.h"

class IdleState : public HeroState {
public:
    HeroState* Update(Hero& hero) override;
    void Enter(Hero& hero) override;
private:
    MoveComponent* move;
};
