#include "ParticleEmitterComponent.h"
#include "Renderer.h"
#include "Random.h"
#include "Camera.h"
#include "Texture.h"
#include "Actor.h"
#include "Game.h"

#include <SDL.h>

const size_t MaxParticles = 1000;

ParticleEmitterComponent::ParticleEmitterComponent(Actor* owner, int drawOrder)
    : Component(owner, drawOrder),
      particlePool(MaxParticles),
      texture(nullptr),
      drawOrder(drawOrder) {
    owner->GetGame()->GetRenderer()->AddParticles(this);
}

ParticleEmitterComponent::~ParticleEmitterComponent() {
    owner->GetGame()->GetRenderer()->RemoveParticles(this);
}

void ParticleEmitterComponent::Update(float deltaTime) {
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

void ParticleEmitterComponent::Draw(Renderer* renderer) {
    if (!texture) return;

    for (auto& particle : particlePool) {
	if (!particle.active) continue;

	float life = particle.lifeRemaining / particle.lifetime;
	Vector4 color = Vector4::Lerp(particle.colorEnd, particle.colorBegin, life);
	texture->SetColor(color);
	
	Vector2 pos = particle.position;
	float size = Math::Lerp(particle.sizeEnd, particle.sizeBegin, life) * Game::UnitsToPixels;

	SDL_Rect dst;
	dst.w = static_cast<int>(size);
	dst.h = static_cast<int>(size);

	Vector2 cameraPos = renderer->GetCamera()->GetPosition();
	dst.x = static_cast<int>((pos.x - cameraPos.x) * Game::UnitsToPixels - (size * 0.5f));
	dst.y = static_cast<int>((pos.y - cameraPos.y) * Game::UnitsToPixels - (size * 0.5f));

	SDL_RenderCopyEx(renderer->renderer,
			 texture->texture,
			 nullptr,
			 &dst,
			 Math::ToDegrees(particle.rotation),
			 nullptr, // Rotate around the center of the texture
			 SDL_FLIP_NONE);
    }
}

void ParticleEmitterComponent::Emit(const ParticleProps& props, int amount) {
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

	particle.lifetime = props.lifetime;
	particle.lifeRemaining = props.lifetime;
	particle.sizeBegin = props.sizeBegin + props.sizeVariation * (Random::GetFloat() - 0.5f);
	particle.sizeEnd = props.sizeEnd;

	poolIndex = ++poolIndex % particlePool.size();
    }
}
