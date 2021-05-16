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
class ParticleEmitterComponent : public Component {
public:
    ParticleEmitterComponent(class Actor* owner, int drawOrder = 200);
    ~ParticleEmitterComponent();

    void Update(float deltaTime) override;
    void Draw(class Renderer* renderer);

    void Play();
    void Stop();

    void SetTexture(class Texture* texture) { this->texture = texture; }
    void SetProps(const ParticleProps& particleProps) { this->particleProps = particleProps; }
    void SetEmissionRate(int emissionRate) { this->emissionRate = emissionRate; }
    void SetEmissionDuration(float emissionDuration) { this->emissionDuration = emissionDuration; }
    void SetIsLooping(bool looping) { this->looping = looping; }
    
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

    enum class State {
	Playing,
 	Stopped
    };

    std::vector<Particle> particlePool;
    size_t poolIndex = 999;

    class Texture* texture;
    ParticleProps particleProps;
    State state;
    
    int drawOrder;
    int emissionRate;
    float emissionDuration;
    float elapsedTime;
    bool looping;
};
