#include "ParticleSystem.h"
#include "Renderer.h"
#include "Random.h"

#include <SDL.h>

Particle::Particle(Vector2 position) {
    this->position.x = position.x - 5 + (Random::GetFloatRange(0.0f, 25.0f));
    this->position.y = position.y - 5 + (Random::GetFloatRange(0.0f, 25.0f));
    lifetime = Random::GetIntRange(0, 5);
}

void Particle::Draw(Renderer* renderer) {
    SDL_Rect dst = { static_cast<int>(position.x), static_cast<int>(position.y), 4, 4 };
    renderer->DrawTexture(texture, &dst);
}

void Particle::Update(float deltaTime) {
    lifetime++;
}
