#include "ParticleSystem.h"
#include "Renderer.h"
#include "Random.h"

#include <SDL.h>

Particle::Particle(Game* game)
    : Actor(game), lifetime(10)  {}

void Particle::UpdateActor(float deltaTime) {
    lifetime++;
}
