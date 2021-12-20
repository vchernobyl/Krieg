#pragma once

#include "ColliderComponent.h"
#include "Maths.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner, const Vector2& size);
};
