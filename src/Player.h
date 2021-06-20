#pragma once

#include "Actor.h"

class RigidbodyComponent;
class SpriteComponent;
class InputSystem;
class Game;

class Player : public Actor {
public:
    Player(Game* game);
    void ActorInput(const InputState& inputState) override;
    void UpdateActor(float deltaTime) override;
private:
    RigidbodyComponent* rigidbody;
    SpriteComponent* sprite;

    Vector2 velocity;
    Vector2 direction;
    bool isJumping = false;
};
