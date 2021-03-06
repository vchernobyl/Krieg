#pragma once

#include "HeroState.h"
#include "AnimSpriteComponent.h"
#include "MoveComponent.h"
#include "JumpComponent.h"

class RunningState : public HeroState {
public:
    HeroState* Update(Hero& hero) override;
    void Enter(Hero& hero) override;
private:
    AnimSpriteComponent* anim;
    MoveComponent* move;
    JumpComponent* jump;
};
