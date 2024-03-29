#pragma once

#include "Maths.h"

class Camera {
public:
    Camera(float screenWidth, float screenHeight);

    void Update();

    const Matrix4& GetViewMatrix() const { return view; }

    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2& position) { this->position = position; needsUpdate = true; }

    float GetScale() const { return scale; }
    void SetScale(float scale) { this->scale = scale; needsUpdate = true; }

    Vector2 ScreenToWorld(const Vector2& screenPoint);

    bool IsBoxInView(const Vector2& position, const Vector2& size);

private:
    bool needsUpdate = true;

    float scale = 48.0f;
    float screenWidth = 0.0f;
    float screenHeight = 0.0f;

    Vector2 position;
    Matrix4 view;
    Matrix4 orthoProjection;
};
