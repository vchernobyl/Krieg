#pragma once

#include <Engine.h>

class Explosion : public Actor {
public:
    Explosion(Game* game, const Vector2& position);
    void UpdateActor(float deltaTime) override;
private:
    float time = 0.0f;
    float lifeTime = 1.5f;
};
