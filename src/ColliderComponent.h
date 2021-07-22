#pragma once

#include "Component.h"
#include "Math.h"

class Actor;
class RigidbodyComponent;
class b2Fixture;

enum class CollisionCategory : unsigned short {
    None    = 0x0000,
    Player  = 0x0002, // 0x0001 is reserved for the default category bit by the Box2D.
    Enemy   = 0x0004,
    Bullet  = 0x0008,
    Ground  = 0x0010,
    Default = 0xFFFF,
};

CollisionCategory operator|(CollisionCategory lhs, CollisionCategory rhs);

struct Manifold {
    Vector2 contactNormal;
    Vector2 contactPoint;
};

class ColliderComponent : public Component {
public:
    ColliderComponent(Actor* owner);
    ~ColliderComponent();

    RigidbodyComponent* GetAttachedRigidbody() const;

    void SetCollisionFilter(CollisionCategory category, CollisionCategory mask);
    void SetSensor(bool flag);

protected:
    b2Fixture* fixture;
};
