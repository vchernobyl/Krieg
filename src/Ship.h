#pragma once

#include "Actor.h"
#include "Math.h"
#include <vector>

class Ship : public Actor {
public:
    Ship(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const struct InputState& inputState) override;

    const std::vector<class Weapon*>& GetWeapons() const { return weapons; }
    const Weapon* GetSelectedWeapon() const { return weapons[selectedWeapon]; }

private:
    class RigidbodyComponent* rigidbody = nullptr;
    class ParticleComponent* trailEmitter = nullptr;

    std::vector<class Weapon*> weapons;
    int selectedWeapon = 0;

    int health = 100;

    Vector2 moveTargetPosition;
    Vector2 direction = Vector2::Right;
};
