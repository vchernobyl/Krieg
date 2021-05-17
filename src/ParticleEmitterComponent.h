#pragma once

#include "Math.h"
#include "Component.h"

#include <vector>

struct ParticleProps {
    Vector2 position;
    Vector2 velocity, velocityVariation;
    Vector4 colorBegin, colorEnd;
    float sizeBegin, sizeEnd, sizeVariation;
    float lifetime = 1.0f;
};

// TODO: Probably need to rename to ParticleComponent.
class ParticleEmitterComponent : public Component {
public:
    ParticleEmitterComponent(class Actor* owner, int drawOrder = 200);
    ~ParticleEmitterComponent();

    void Update(float deltaTime) override;
    void Draw(class Renderer* renderer);

    void Emit(const ParticleProps& props, int amount);

    void SetTexture(class Texture* texture) { this->texture = texture; }
    
    int GetDrawOrder() const { return drawOrder; }
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
    
    int drawOrder;
};
