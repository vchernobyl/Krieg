#pragma once

#include "Math.h"

class Camera {
public:
    Camera(int viewportWidth, int viewportHeight);

    void Follow(class Actor* owner);

    void SetPosition(Vector2 position) { this->position = position; }
    const Vector2& GetPosition() const { return position; }

    void SetWorldSize(int width, int height) { worldSize = Vector2(width, height); }
    const Vector2& GetWorldSize() const { return worldSize; }
private:
    int viewportWidth;
    int viewportHeight;
    Vector2 position;
    Vector2 worldSize;
};
