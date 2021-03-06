#pragma once

#include "Actor.h"
#include "InputSystem.h"
#include "HeroState.h"
#include "AnimSpriteComponent.h"
#include "MoveComponent.h"
#include "JumpComponent.h"

class Hero : public Actor {
public:
    Hero(class Game* game);
    ~Hero() { delete state; }
    void ActorInput(const InputState& inputState) override;
private:
    AnimSpriteComponent* animation;
    MoveComponent* move;
    JumpComponent* jump;
    HeroState* state;
    AnimDirection direction;
};
