#pragma once

#include "Component.h"
#include "Math.h"

enum class CollisionLayer {
    Default = 1,
    Player = 2,
    Tile = 3
};

struct CollisionInfo {
    bool colliding = false;
    Vector2 contactPoint;
    Vector2 contactNormal;
    float contactTime;
    class ColliderComponent* other;
};

class ColliderComponent : public Component {
public:
    ColliderComponent(class Actor* owner);
    ~ColliderComponent();

    virtual CollisionInfo Intersects(ColliderComponent* other, float deltaTime) = 0;
    virtual void ResolveCollision(const CollisionInfo& info) = 0;

    CollisionLayer GetLayer() const { return layer; }
    void SetLayer(CollisionLayer layer) { this->layer = layer; }

    class RigidbodyComponent* GetAttachedRigidbody() const;
private:
    CollisionLayer layer;
};
