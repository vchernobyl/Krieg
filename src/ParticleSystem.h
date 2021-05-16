#pragma once

#include "Math.h"
#include "Component.h"

#include <vector>

struct ParticleProps {
    Vector2 velocity, velocityVariation;
    Vector4 colorBegin, colorEnd;
    float sizeBegin, sizeEnd, sizeVariation;
    float lifetime = 1.0f;
};

// TODO: Probably need to rename to ParticleComponent.
class ParticleSystem : public Component {
public:
    ParticleSystem(class Actor* owner, int drawOrder = 200);
    ~ParticleSystem();

    void Update(float deltaTime) override;
    void Draw(class Renderer* renderer);

    void SetTexture(class Texture* texture) { this->texture = texture; }
    void SetProps(const ParticleProps& particleProps) { this->particleProps = particleProps; }
    void SetAmount(int amount) { this->amount = amount; }
    
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
    ParticleProps particleProps;
    
    int drawOrder;
    int amount;
};
