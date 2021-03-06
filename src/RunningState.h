#pragma once

#include "HeroState.h"
#include "AnimSpriteComponent.h"
#include "MoveComponent.h"

class RunningState : public HeroState {
public:
    HeroState* ProcessInput(Hero& hero, const InputState& input) override;
    void Update(Hero& hero) override;
    void Enter(Hero& hero) override;
private:
    AnimSpriteComponent* anim;
    MoveComponent* move;
};
