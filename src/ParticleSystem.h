#pragma once

#include "Math.h"

class Renderer;
struct SDL_Texture;

const int TotalParticles = 20;

class Particle {
public:
    Particle(Vector2 position);
    void Draw(Renderer* renderer);
    void Update(float deltaTime);
    bool IsDead() const { return lifetime <= 0; }
private:
    Vector2 position;
    int lifetime;
    SDL_Texture* texture;
};
