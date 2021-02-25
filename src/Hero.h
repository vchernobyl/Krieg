#pragma once

#include "Actor.h"
#include "InputSystem.h"
#include "AnimSpriteComponent.h"
#include "MovementComponent.h"
#include "RigidbodyComponent.h"

class Hero : public Actor {
public:
    enum AnimState { Idle = 0, Run = 1, Attack = 2 };
    Hero(class Game* game);
    void ActorInput(const InputState& inputState) override;
private:
    AnimSpriteComponent* animation;
    MovementComponent* movement;
    AnimState animState;
};
