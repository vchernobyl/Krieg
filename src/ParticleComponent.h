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
    float lifeTime = 1.0f;
};

class Actor;
class Renderer;
class Texture;

// TODO: Convert to OpenGL.
class ParticleComponent : public Component {
public:
    ParticleComponent(Actor* owner, int drawOrder = 200);
    ~ParticleComponent();

    void Update(float deltaTime) override;
    void Draw(class SpriteBatch& spriteBatch);

    void Emit(const ParticleProps& props, int amount);
    void Start() { isRunning = true; }
    void Stop() { isRunning = false; }

    void SetTexture(Texture* texture) { this->texture = texture; }
    void SetProps(const ParticleProps& props) { this->props = props; }
    void SetEmissionRate(float emissionRate) { this->emissionRate = emissionRate; }
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
        float lifeTime = 1.0f;
        float lifeRemaining = 0.0f;
        bool active = false;
    };

    std::vector<Particle> particlePool;
    size_t poolIndex = 0;

    Texture* texture;
    
    int drawOrder;

    bool isRunning = false;
    std::function<void(void)> onEmissionEnd;

    ParticleProps props;
    float emissionRate = 3.0f;
    float time = 0.0f;
};
