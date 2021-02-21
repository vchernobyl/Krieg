#pragma once

#include "Actor.h"
#include "AnimSpriteComponent.h"
#include "RigidbodyComponent.h"

class Skeleton : public Actor {
public:
    enum AnimState { Idle = 0, Run = 1 };
    Skeleton(class Game* game);
    void ActorInput(const uint8_t* keyState) override;
    void UpdateActor(float deltaTime) override;
private:
    AnimSpriteComponent* animation;
    RigidbodyComponent* rigidbody;
    AnimState animState;
};
