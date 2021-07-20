#pragma once

#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Math.h"

enum class CollisionCategory {
    Player = 0x0001,
    Enemy  = 0x0002,
    Bullet = 0x0004,
};

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner, const Vector2& size);
};
