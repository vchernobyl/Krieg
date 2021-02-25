#pragma once

#include "Actor.h"
#include "AnimSpriteComponent.h"
#include "MovementComponent.h"
#include "RigidbodyComponent.h"

class Hero : public Actor {
public:
    enum AnimState { Idle = 0, Run = 1, Attack = 2 };
    Hero(class Game* game);
private:
    AnimSpriteComponent* animation;
    MovementComponent* input;
    AnimState animState;
};
