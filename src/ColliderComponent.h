#pragma once

#include "Component.h"
#include "Math.h"

struct CollisionInfo {
    bool colliding = false;
    Vector2 penetration;
    Vector2 normal;
    class ColliderComponent* other;
};

class ColliderComponent : public Component {
public:
    ColliderComponent(class Actor* owner);
    ~ColliderComponent();

    class RigidbodyComponent* GetAttachedRigidbody() const;
};
