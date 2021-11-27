#pragma once

#include "Actor.h"
#include <vector>
#include <string>

class Game;
class TargetComponent;
struct InputState;

class Weapon : public Actor {
public:
    Weapon(Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;

    virtual void ShootAt(TargetComponent* target) = 0;
    virtual std::string GetWeaponName() const = 0;
    virtual Vector4 GetReticleColor() const = 0;
    
    int GetWeaponStacks() const { return stacks; }

    bool IsTargeted(TargetComponent* target) const;
    void AddTarget(TargetComponent* target);
    void RemoveTarget(TargetComponent* target);

    const std::vector<TargetComponent*>& GetTargets() const { return targets; }

protected:
    std::vector<TargetComponent*> targets;
    int stacks = 3;
    int currentTargetIndex = 0;

    float fireRate = 1.0f;
    float timeBetweenShots = 0.0f;
};
