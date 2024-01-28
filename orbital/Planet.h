#pragma once

#include <Engine.h>

class Planet : public Actor {
public:
    Planet(Game* game, const Vector2& center, float radius);
    void UpdateActor(float deltaTime) override;

    const Vector2& GetCenter() { return center; }
    float GetRadius() const { return radius; }
    void SetRadius(float radius) { this->radius = radius; }

private:
    Vector2 center;
    float radius;
};
