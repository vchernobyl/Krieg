#pragma once

#include "Component.h"
#include "Math.h"

class CircleComponent : public Component {
public:
    CircleComponent(class Actor* owner);
    float GetRadius() const { return radius; }
    void SetRadius(float radius) { this->radius = radius; }
    const Vector2& GetCenter() const;
private:
    float radius;
};

bool Intersect(const CircleComponent&, const CircleComponent&);
