#pragma once

#include "Component.h"
#include "Math.h"

struct CollisionInfo {
    bool colliding = false;
    Vector2 penetrationVector;
};

class ColliderComponent : public Component {
public:
    ColliderComponent(class Actor* owner);
    ~ColliderComponent();

    virtual CollisionInfo Intersects(ColliderComponent* other, float deltaTime) = 0;
    virtual void ResolveCollision(const CollisionInfo& info) = 0;

    class RigidbodyComponent* GetAttachedRigidbody() const;

    bool isTrigger = false;
};
