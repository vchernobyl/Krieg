#pragma once

#include "Component.h"
#include "Math.h"

class CameraComponent : public Component {
public:
    CameraComponent(class Actor* owner, int updateOrder = 200);
    void ProcessInput(const struct InputState& inputState) override;
    void Update(float deltaTime) override;

private:
    void SetViewMatrix(const Matrix4& view);

    float scale = 0.0f;
    Vector2 position = Vector2::Zero;
};
