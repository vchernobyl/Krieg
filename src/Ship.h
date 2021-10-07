#pragma once

#include "Actor.h"
#include "InputSystem.h"

class Ship : public Actor {
public:
    Ship(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ActorInput(const InputState& inputState) override;

private:
    float laserCooldown;
};
