#pragma once

#include "Actor.h"
#include "InputSystem.h"

class Player : public Actor {
public:
    Player(class Game* game);
    void ActorInput(const InputState& inputState) override;
    void UpdateActor(float deltaTime) override;
private:
    Vector2 velocity;
};
