#pragma once

#include "Component.h"
#include "Maths.h"

class Actor;
class RigidbodyComponent;
class b2Fixture;

// TODO: This is currently very gameplay specific, our
// mask should probably be a regular numeric value instead.
enum class CollisionCategory : unsigned short {
    None    = 0x0000,
    Player  = 0x0002, // 0x0001 is reserved for the default category bit by the Box2D.
    Enemy   = 0x0004,
    Bullet  = 0x0008,
    Ground  = 0x0010,
    Default = 0xFFFF,
};

// TODO: Implement the rest of the operators.
CollisionCategory operator|(CollisionCategory lhs, CollisionCategory rhs);

struct Contact {
    Vector2 normal;
    Vector2 point;
    Actor* other;
};

class ColliderComponent : public Component {
public:
    ColliderComponent(Actor* owner);
    ~ColliderComponent();

    RigidbodyComponent* GetAttachedRigidbody() const;

    [[deprecated]]
    void SetCollisionFilter(CollisionCategory category, CollisionCategory mask = CollisionCategory::Default);
    void SetCategoryAndMask(unsigned short category, unsigned short mask);
    
    void SetSensor(bool flag);
    bool IsSensor() const;

protected:
    b2Fixture* fixture;
};
