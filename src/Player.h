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
    void OnBeginContact(const Manifold& manifold) override;
private:
    static constexpr float Speed = 15.0f;
    static constexpr float SpreadVariation = 0.4f;
};    

class Player : public Actor {
public:
    Player(Game* game);
    void ActorInput(const InputState& inputState) override;
    void UpdateActor(float deltaTime) override;
private:
    static constexpr float MaxVelocity = 10.0f;
    static constexpr float Acceleration = 27.5f;
    static constexpr float Deceleration = 5.0f;
    static constexpr float JumpImpulse = 17.0f;

    ParticleEmitterComponent* particles;
    RigidbodyComponent* rigidbody;
    SpriteComponent* sprite;
    AudioComponent* audio;

    Vector2 velocity;
    Vector2 direction;
};
