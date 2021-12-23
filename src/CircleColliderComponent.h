#pragma once

#include "ColliderComponent.h"

class Actor;
class Vector2;

class CircleColliderComponent : public ColliderComponent {
public:
    CircleColliderComponent(Actor* owner, float radius, const Vector2& center = Vector2::Zero);
    float GetRadius() const;
};
