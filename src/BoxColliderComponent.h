#pragma once

#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Math.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner);
    ~BoxColliderComponent();
    void SetBox(float width, float height);
};
