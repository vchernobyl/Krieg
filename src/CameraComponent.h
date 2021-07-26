#pragma once

#include "Component.h"
#include "Math.h"

class CameraComponent : public Component {
public:
    CameraComponent(class Actor* owner);
    void Update(float deltaTime) override;
    void SetBounds(const Rectangle& bounds) { this->bounds = bounds; }
private:
    void SetView(const Vector2& view);

    Vector2 position;
    Vector2 viewport;
    Rectangle bounds;

    float time = 0.0f;
};
