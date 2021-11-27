#pragma once

#include "Actor.h"
#include <vector>

class Game;
class TargetComponent;
struct InputState;

class Weapon : public Actor {
public:
    Weapon(Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;
    virtual void ShootAt(TargetComponent* target) = 0;

protected:
    bool IsTargeted(TargetComponent* target) const;
    void AddTarget(TargetComponent* target);
    void RemoveTarget(TargetComponent* target);

    std::vector<TargetComponent*> targets;
    int stacks = 3;
    int currentTargetIndex = 0;

    bool isActivated = false;

    float fireRate = 1.0f;
    float timeBetweenShots = 0.0f;
};
