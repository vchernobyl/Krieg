#pragma once

#include "Actor.h"

class ColliderComponent;
class BoxColliderComponent;
class RigidbodyComponent;
class SpriteComponent;
class AudioComponent;
class ParticleEmitterComponent;
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

    Vector2 velocity;
    Vector2 direction;
    bool isJumping = false;
};
