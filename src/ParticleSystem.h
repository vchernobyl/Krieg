#pragma once

#include "Math.h"
#include <vector>

struct ParticleProps {
    Vector2 position;
    Vector2 velocity, velocityVariation;
    Vector4 colorBegin, colorEnd;
    float sizeBegin, sizeEnd, sizeVariation;
    float lifetime = 1.0f;
};

class ParticleSystem {
public:
    ParticleSystem();
    void Update(float deltaTime);
    void Draw(class Renderer* renderer);
    void Emit(const ParticleProps& particleProps);
    void SetTexture(class Texture* texture) { this->texture = texture; }
private:
    struct Particle {
	Vector2 position;
	Vector2 velocity;
	Vector4 colorBegin, colorEnd;
	float rotation = 0.0f;
	float sizeBegin, sizeEnd;
	float lifetime = 1.0f;
	float lifeRemaining = 0.0f;
	bool active = false;
    };

    std::vector<Particle> particlePool;
    size_t poolIndex = 999;

    class Texture* texture;
};
