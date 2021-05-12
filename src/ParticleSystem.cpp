#include "ParticleSystem.h"
#include "Renderer.h"
#include "Random.h"

const size_t MaxParticles = 1000;

ParticleSystem::ParticleSystem()
    : particlePool(MaxParticles) {}

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

void ParticleSystem::Draw(Renderer* renderer) {}

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

