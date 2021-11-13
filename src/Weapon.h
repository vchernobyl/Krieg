#pragma once

#include "Actor.h"
#include <vector>

class Game;
class Damageable;
struct InputState;

class Weapon : public Actor {
public:
    Weapon(Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;
    virtual void ShootAt(Damageable* target) = 0;

protected:
    bool IsTargeted(Damageable* target) const;
    void AddTarget(Damageable* target);
    void RemoveTarget(Damageable* target);

    std::vector<Damageable*> targets;
    int stacks = 3;
    int currentTargetIndex = 0;

    bool isActivated = false;

    float fireRate = 1.0f;
    float timeBetweenShots = 0.0f;
};
