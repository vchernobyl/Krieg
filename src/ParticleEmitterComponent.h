#pragma once

#include "Math.h"
#include "Component.h"

#include <vector>
#include <functional>

struct ParticleProps {
    Vector2 position;
    Vector2 velocity, velocityVariation;
    Vector4 colorBegin, colorEnd;
    float sizeBegin, sizeEnd, sizeVariation;
    float rotationBegin, rotationSpeed;
    float lifetime = 1.0f;
};

class Actor;
class Renderer;
class Texture;

// TODO: Probably need to rename to ParticleComponent.
class ParticleEmitterComponent : public Component {
public:
    ParticleEmitterComponent(Actor* owner, int drawOrder = 200);
    ~ParticleEmitterComponent();

    void Update(float deltaTime) override;
    void Draw(Renderer* renderer);

    void Emit(const ParticleProps& props, int amount);

    void SetTexture(Texture* texture) { this->texture = texture; }
    void SetOnEmissionEnd(std::function<void(void)> onEmissionEnd) { this->onEmissionEnd = onEmissionEnd; }

    int GetDrawOrder() const { return drawOrder; }
private:
    struct Particle {
	Vector2 position;
	Vector2 velocity;
	Vector4 colorBegin, colorEnd;
	float rotation = 0.0f;
	float rotationSpeed = 0.0f;
	float sizeBegin, sizeEnd;
	float lifetime = 1.0f;
	float lifeRemaining = 0.0f;
	bool active = false;
    };

    std::vector<Particle> particlePool;
    size_t poolIndex = 0;

    Texture* texture;
    
    int drawOrder;

    bool isRunning = false;
    bool destroyOnEnd = false;
    std::function<void(void)> onEmissionEnd;
};
