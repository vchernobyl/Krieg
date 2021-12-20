#pragma once

#include "Component.h"
#include "Maths.h"

class CameraMovement : public Component {
public:
    CameraMovement(class Actor* owner, int updateOrder = 200);
    void ProcessInput(const struct InputState& inputState) override;
private:
    Vector2 dragStart;
    Vector2 dragEnd;
    class Camera* camera;
};
