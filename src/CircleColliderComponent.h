#pragma once

#include "ColliderComponent.h"

class Actor;
class Vector2;

class CircleColliderComponent : public ColliderComponent {
public:
    CircleColliderComponent(Actor* owner, const Vector2& center, float radius);
};
