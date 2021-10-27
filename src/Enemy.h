#pragma once

#include "Actor.h"

class Enemy : public Actor {
public:
    Enemy(class Game*);
    void UpdateActor(float deltaTime) override;
    void Select() { isSelected = !isSelected; }
private:
    class RigidbodyComponent* rigidbody = nullptr;
    Actor* followTarget = nullptr;
    bool isSelected = false;
};
