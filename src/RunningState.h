#pragma once

#include "HeroState.h"
#include "AnimSpriteComponent.h"
#include "MoveComponent.h"

class RunningState : public HeroState {
public:
    HeroState* Update(Hero& hero) override;
    void Enter(Hero& hero) override;
private:
    AnimSpriteComponent* anim;
    MoveComponent* move;
};
