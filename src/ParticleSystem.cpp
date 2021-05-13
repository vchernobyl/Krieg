#include "ParticleSystem.h"
#include "Renderer.h"
#include "Random.h"
#include "Camera.h"
#include "Texture.h"

#include <SDL.h>

const size_t MaxParticles = 1000;

ParticleSystem::ParticleSystem() : particlePool(MaxParticles), texture(nullptr) {}

void ParticleSystem::Update(float deltaTime) {
    for (auto& particle : particlePool) {
	if (!particle.active) continue;

	if (particle.lifeRemaining <= 0.0f) {
	    particle.active = false;
	    continue;
	}

	particle.lifeRemaining -= deltaTime;
	particle.position += particle.velocity * deltaTime;
	particle.rotation += 0.01f * deltaTime;
    }
}

void ParticleSystem::Draw(Renderer* renderer) {
    if (!texture) return;
    
    for (auto& particle : particlePool) {
	if (!particle.active) continue;

	float life = particle.lifeRemaining / particle.lifetime;
	Vector4 color = Vector4::Lerp(particle.colorEnd, particle.colorBegin, life);

	// TODO: Set alpha
	texture->SetColor(Vector3(color.x, color.y, color.z));
	
	Vector2 pos = particle.position;
	int size = Math::Lerp(particle.sizeEnd, particle.sizeBegin, life);
	SDL_Rect dst = { static_cast<int>(pos.x), static_cast<int>(pos.y), size, size };
	renderer->GetCamera()->ToScreenSpace(dst);
	SDL_RenderCopyEx(renderer->GetSDLRenderer(), texture->texture, nullptr, &dst, 0, nullptr, SDL_FLIP_NONE);
    }
}

void ParticleSystem::Emit(const ParticleProps& particleProps) {
    Particle& particle = particlePool[poolIndex];
    particle.active = true;
    particle.position = particleProps.position;
    particle.rotation = Random::GetFloat() * Math::TwoPi;

    particle.velocity = particleProps.velocity;
    particle.velocity.x += particleProps.velocityVariation.x * (Random::GetFloat() - 0.5f);
    particle.velocity.y += particleProps.velocityVariation.y * (Random::GetFloat() - 0.5f);

    particle.colorBegin = particleProps.colorBegin;
    particle.colorEnd = particleProps.colorEnd;

    particle.lifetime = particleProps.lifetime;
    particle.lifeRemaining = particleProps.lifetime;
    particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation * (Random::GetFloat() - 0.5f);
    particle.sizeEnd = particleProps.sizeEnd;

    poolIndex = --poolIndex % particlePool.size();
}
