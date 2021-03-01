#pragma once

#include "Actor.h"
#include "InputSystem.h"
#include "AnimSpriteComponent.h"
#include "MoveComponent.h"

class Hero : public Actor {
public:
    enum AnimState { Idle = 0, Run = 1 };
    Hero(class Game* game);
    void ActorInput(const InputState& inputState) override;
    void UpdateActor(float deltaTime) override;
private:
    AnimSpriteComponent* animation;
    MoveComponent* movement;
    AnimState animState;
};
