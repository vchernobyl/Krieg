#pragma once

#include "Actor.h"

class ParticleEmitterComponent;
class RigidbodyComponent;
class SpriteComponent;
class AudioComponent;
class InputSystem;
class Game;

class MuzzleFlash : public Actor {
public:
    MuzzleFlash(Game* game);
    void UpdateActor(float deltaTime) override;
private:
    float time = 0.0f;
};

class Bullet : public Actor {
public:
    Bullet(Game* game, Vector2 direction, Vector2 position);
    void OnBeginContact() override;
private:
    static const float Speed;
    static const float SpreadVariation;
};    

class Player : public Actor {
public:
    Player(Game* game);
    void ActorInput(const InputState& inputState) override;
    void UpdateActor(float deltaTime) override;
private:
    static const float MaxVelocity;
    static const float Acceleration;
    static const float Deceleration;
    static const float JumpImpulse;

    ParticleEmitterComponent* particles;
    RigidbodyComponent* rigidbody;
    SpriteComponent* sprite;
    AudioComponent* audio;

    Vector2 velocity;
    Vector2 direction;
};
