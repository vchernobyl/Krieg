#pragma once

#include "Actor.h"
#include <vector>

class Game;
class Damageable;
struct InputState;

// This will be used for rockets and bullets.
class Projectile : public Actor {
public:
};

class Weapon : public Actor {
public:
    Weapon(Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;
    virtual void Shoot() = 0;

private:
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
