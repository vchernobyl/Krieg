#pragma once

#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Math.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner);
    ~BoxColliderComponent();

    void SetSize(float width, float height, bool isSensor);
    void SetSize(const Vector2& size, bool isSensor = false) { SetSize(size.x, size.y, isSensor); }
};
