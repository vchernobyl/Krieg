#pragma once

#include "Actor.h"
#include "AnimSpriteComponent.h"
#include "MovementComponent.h"

class Hero : public Actor {
public:
    enum AnimState { Idle = 0, Run = 1, Attack = 2 };
    Hero(class Game* game);
    void ActorInput(const uint8_t* keyState) override;
private:
    AnimSpriteComponent* animation;
    MovementComponent* input;
    AnimState animState;
};
