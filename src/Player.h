#pragma once

#include "Actor.h"

class RigidbodyComponent;
class SpriteComponent;
class AudioComponent;
class InputSystem;
class Game;

class Bullet : public Actor {
public:
    Bullet(Game* game, Vector2 direction, Vector2 position);
    void OnBeginContact() override;
};    

class Player : public Actor {
public:
    Player(Game* game);
    void ActorInput(const InputState& inputState) override;
    void UpdateActor(float deltaTime) override;
private:
    RigidbodyComponent* rigidbody;
    SpriteComponent* sprite;
    AudioComponent* audio;

    Vector2 velocity;
    Vector2 direction;
};
