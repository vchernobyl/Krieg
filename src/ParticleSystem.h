#pragma once

#include "Math.h"
#include "Actor.h"

#include <vector>

class Game;
class Renderer;
struct SDL_Texture;

class Particle : public Actor {
public:
    Particle(Game* game);
    void UpdateActor(float deltaTime) override;
    bool IsDead() const { return lifetime <= 0; }
private:
    Vector2 position;
    int lifetime;
    SDL_Texture* texture;
};

class ParticleSystem : public Actor {
public:
    ParticleSystem(Game* game, int maxParticles = 100);
    void UpdateActor(float deltaTime) override;
private:
    std::vector<Particle*> particles;
};
