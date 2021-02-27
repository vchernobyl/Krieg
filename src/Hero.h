#pragma once

#include "Actor.h"
#include "InputSystem.h"
#include "AnimSpriteComponent.h"
#include "MovementComponent.h"
#include "RigidbodyComponent.h"

class Hero : public Actor {
public:
    enum AnimState { Idle = 0, Run = 1, Attack = 2, Jump = 3 };
    Hero(class Game* game);
    void ActorInput(const InputState& inputState) override;
    void UpdateActor(float deltaTime) override;
private:
    AnimSpriteComponent* animation;
    MovementComponent* movement;
    AnimState animState;
};
