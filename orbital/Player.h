#pragma once

#include <Engine.h>

class Player : public Actor {
public:
    int score = 0;

    Player(Game* game);
    void ActorInput(const InputState& input) override;
    void UpdateActor(float deltaTime) override;
private:
    float angle = 90.0f;
    float speed = 1.5f;
    float orbitSpeed = 2.5f;

    float fireRate = 0.35f;
    float time = 0.0f;

    AudioComponent* rocketSound = nullptr;
};
