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
    time += deltaTime;

    if (time >= 1.0f / emissionRate) {
        if (isRunning) {
            Emit(props, 1);
            time = 0.0f;
        }
    }

    for (auto& particle : particlePool) {
        if (!particle.active) {
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
}

void ParticleComponent::Draw(SpriteBatch& spriteBatch) {
    for (auto& particle : particlePool) {
        if (!particle.active) continue;

        auto t = 1.0f - particle.lifeRemaining / particle.lifeTime;
        auto size = Math::Lerp(particle.sizeBegin, particle.sizeEnd, t);

        // Draw the particle at the center of the position.
        auto dest = Vector4(particle.position.x - size / 2.0f,
                            particle.position.y - size / 2.0f,
                            size, size);

        auto uv = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

        auto color = Vector4::Lerp(particle.colorBegin, particle.colorEnd, t);
        spriteBatch.Draw(dest, uv, texture->GetID(), GetDrawOrder(), color, particle.rotation);
    }
}

void ParticleComponent::Emit(const ParticleProps& props, int amount) {
    isRunning = true;

    auto position = owner->GetPosition();

    for (int i = 0; i < amount; i++) {
        Particle& particle = particlePool[poolIndex];
        particle.active = true;
        particle.position = position;
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
