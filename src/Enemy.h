#pragma once

#include "Actor.h"

class RigidbodyComponent;
class SpriteComponent;
class Game;

class Enemy : public Actor {
public:
    Enemy(Game* game);
    void UpdateActor(float deltaTime) override;
//    void OnBeginContact(const struct Manifold& manifold) override;
private:
    RigidbodyComponent* rigidbody;
    SpriteComponent* sprite;

    float hitTime = 0.0f;
};
