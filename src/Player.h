#pragma once

#include "Actor.h"
#include "ParticleEmitterComponent.h"

class ColliderComponent;
class BoxColliderComponent;
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
    int frames = 0;
};

class Bullet : public Actor {
public:
    Bullet(Game* game, const Vector2& direction);
    void OnTriggerEnter(ColliderComponent* other) override;
private:
    RigidbodyComponent* rigidbody;
    BoxColliderComponent* collider;
    ParticleProps particleProps;
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

    ParticleEmitterComponent* dustParticles;
    ParticleProps particleProps;

    Vector2 velocity;
    Vector2 direction;
    bool isJumping = false;
};
