#pragma once

#include "Actor.h"
#include "Math.h"
#include <vector>

class Ship : public Actor {
public:
    Ship(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;
private:
    class RigidbodyComponent* rigidbody = nullptr;
    class ParticleComponent* trailEmitter = nullptr;

    class RocketLauncher* rocketLauncher = nullptr;
    class Turret* turret = nullptr;
    std::vector<class Weapon*> weapons;

    Vector2 moveTargetPosition;
    Vector2 direction = Vector2::Right;
};
