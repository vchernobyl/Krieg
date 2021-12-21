#pragma once

#include "Engine.h"

class Player : public Actor {
public:
    Player(Game* game);
    void ActorInput(const InputState& input) override;
    void UpdateActor(float deltaTime) override;
private:
    float angle = 90.0f;
    float speed = 3.5f;
};
