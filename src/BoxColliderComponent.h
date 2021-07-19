#pragma once

#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Math.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner);
    ~BoxColliderComponent();

    void SetSize(float width, float height);
    void SetSize(const Vector2& size) { SetSize(size.x, size.y); }
};
