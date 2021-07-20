#pragma once

#include "ColliderComponent.h"
#include "Math.h"

enum class CollisionCategory {
    None    = 0x0000,
    Player  = 0x0002, // 0x0001 is reserved for the default category bit by the Box2D.
    Enemy   = 0x0004,
    Bullet  = 0x0008,
    Ground  = 0x000F,
    Default = 0xFFFF,
};

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner, const Vector2& size);
    void SetCollisionCategory(CollisionCategory category);
    void SetCollisionMask(CollisionCategory category);
};
