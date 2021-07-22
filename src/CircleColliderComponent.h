#pragma once

#include "ColliderComponent.h"

class CircleColliderComponent : public ColliderComponent {
public:
    CircleColliderComponent(class Actor* owner, float radius);
};
