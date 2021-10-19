#pragma once

#include "Component.h"
#include "Math.h"

class CameraComponent : public Component {
public:
    CameraComponent(class Actor* owner, int updateOrder = 200);
    void Update(float deltaTime) override;
protected:
    void SetViewMatrix(const Matrix4& view);
};
