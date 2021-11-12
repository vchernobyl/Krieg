#pragma once

#include "Actor.h"
#include <vector>

class Game;
class SpriteComponent;
class BoxColliderComponent;

class Bullet : public Actor {
public:
    Bullet(Game* game);
private:
    SpriteComponent* sprite = nullptr;
    BoxColliderComponent* collider = nullptr;
};

class Turret : public Actor {
public:
    Turret(Game* game);
    void UpdateActor(float deltaTime) override;
private:
    float fireRate = 8.0f;
    float timeBetweenShots = 0.0f;

    std::vector<const Actor*> targets;
};
