#include "ParticleComponent.h"
#include "Renderer.h"
#include "SpriteBatch.h"
#include "Random.h"
#include "Texture.h"
#include "Actor.h"
#include "Game.h"

const size_t MaxParticles = 1000;

ParticleComponent::ParticleComponent(Actor* owner, int drawOrder)
    : Component(owner, drawOrder),
      particlePool(MaxParticles),
      texture(nullptr),
      drawOrder(drawOrder) {
    owner->GetGame()->GetRenderer()->AddParticles(this);
}

ParticleComponent::~ParticleComponent() {
    owner->GetGame()->GetRenderer()->RemoveParticles(this);
}

void ParticleComponent::Update(float deltaTime) {
    if (!isRunning) return;
    
    int inactive = 0;
    
    for (auto& particle : particlePool) {
        if (!particle.active) {
            inactive++;
            continue;
        }

        if (particle.lifeRemaining <= 0.0f) {
            particle.active = false;
            continue;
        }

        particle.lifeRemaining -= deltaTime;
        particle.position += particle.velocity * deltaTime;
        particle.rotation += particle.rotationSpeed * deltaTime;
    }

    if (isRunning && inactive == MaxParticles) {
        isRunning = false;
        if (onEmissionEnd) {
            onEmissionEnd();
        }
    }
}

void ParticleComponent::Draw(SpriteBatch& spriteBatch) {
    for (auto& particle : particlePool) {
        if (!particle.active) continue;

        auto t = 1.0f - particle.lifeRemaining / particle.lifeTime;
        auto size = Math::Lerp(particle.sizeBegin, particle.sizeEnd, t);
        auto dest = Vector4(particle.position.x, particle.position.y, size, size);

        auto uv = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

        auto color = Vector4::Lerp(particle.colorBegin, particle.colorEnd, t);
        spriteBatch.Draw(dest, uv, texture->GetID(), GetDrawOrder(), color);
    }
}

void ParticleComponent::Emit(const ParticleProps& props, int amount) {
    isRunning = true;

    for (int i = 0; i < amount; i++) {
        Particle& particle = particlePool[poolIndex];
        particle.active = true;
        particle.position = props.position;
        particle.rotation = props.rotationBegin;
        particle.rotationSpeed = props.rotationSpeed;

        particle.velocity = props.velocity;
        particle.velocity.x += props.velocityVariation.x * (Random::GetFloat() - 0.5f);
        particle.velocity.y += props.velocityVariation.y * (Random::GetFloat() - 0.5f);

        particle.colorBegin = props.colorBegin;
        particle.colorEnd = props.colorEnd;

        particle.lifeTime = props.lifeTime;
        particle.lifeRemaining = props.lifeTime;
        particle.sizeBegin = props.sizeBegin + props.sizeVariation * (Random::GetFloat() - 0.5f);
        particle.sizeEnd = props.sizeEnd;

        poolIndex = ++poolIndex % particlePool.size();
    }
}
