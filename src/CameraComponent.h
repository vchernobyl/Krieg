#pragma once

#include "Component.h"
#include "Math.h"

class CameraComponent : public Component {
public:
    CameraComponent(class Actor* owner);
    void Update(float deltaTime) override;
    void SetView(const Vector2& view);
private:
    Vector2 viewport;
};
