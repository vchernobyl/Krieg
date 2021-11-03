#pragma once

#include "Component.h"
#include "Math.h"

// TODO: Instead of the camera component having the core
// camera functionality, it will be extracted to a regular non-component Camera class,
// which will support basically the same API (besides component overrides).
// This camera will be added by default in the renderer. CameraComponent will be just adding some
// functionality on top of the public Camera API. Borrow some ideas from the LibGDX.
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
