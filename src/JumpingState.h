#pragma once

#include "HeroState.h"
#include "JumpComponent.h"
#include "MoveComponent.h"
#include "AnimSpriteComponent.h"

class JumpingState : public HeroState {
public:
    HeroState* ProcessInput(Hero& hero, const InputState& input) override;
    HeroState* Update(Hero& hero) override;
    void Enter(Hero& hero) override;
private:
    JumpComponent* jump;
    MoveComponent* move;
    AnimSpriteComponent* anim;
};
