#pragma once

#include "ColliderComponent.h"
#include "Math.h"

enum class CollisionCategory : unsigned short {
    None    = 0x0000,
    Player  = 0x0002, // 0x0001 is reserved for the default category bit by the Box2D.
    Enemy   = 0x0004,
    Bullet  = 0x0008,
    Ground  = 0x0010,
    Default = 0xFFFF,
};

CollisionCategory operator|(CollisionCategory lhs, CollisionCategory rhs);

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner, const Vector2& size);

    // TODO: This will have to be common for all colliders, has to be pulled up the hierarchy.
    // This will do for now until we have other types of colliders.
    void SetCollisionFilter(CollisionCategory category, CollisionCategory mask);
    void SetSensor(bool flag);

private:
    class b2Fixture* fixture;
};
