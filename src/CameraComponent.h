#pragma once

#include "Component.h"
#include "Math.h"

class CameraComponent : public Component {
public:
    CameraComponent(class Actor* owner, int updateOrder = 300);
    void Update(float deltaTime) override;
    void SetBounds(const Rectangle& bounds) { this->bounds = bounds; }
private:
    void SetView(const Vector2& view);

    Vector2 position;
    Vector2 viewport;
    Rectangle bounds;

    float velocityX = 0.0f;
    float velocityY = 0.0f;
};
