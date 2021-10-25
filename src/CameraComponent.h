#pragma once

#include "Component.h"
#include "Math.h"

class CameraComponent : public Component {
public:
    CameraComponent(class Actor* owner, int updateOrder = 200);
    void ProcessInput(const struct InputState& inputState) override;
    void Update(float deltaTime) override;

    Vector2 ScreenToWorld(const Vector2& screenPoint);

    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2& position) { this->position = position; needsUpdate = true; }

private:
    bool needsUpdate = true;
    Vector2 dragStart;
    Vector2 dragEnd;

    float scale = 48.0f;
    float screenWidth = 0.0f;
    float screenHeight = 0.0f;

    Vector2 position;
    Matrix4 view;
    Matrix4 orthoProjection;
};
