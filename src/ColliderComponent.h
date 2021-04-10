#pragma once

#include "Component.h"
#include "Math.h"

enum class CollisionLayer {
    Default = 1,
    Player = 2,
    Tile = 3
};

struct Manifold {
    bool colliding = false;
    Vector2 contactPoint;
    Vector2 contactNormal;
    float contactTime;
    Rect* other;
};

struct CollisionInfo {
    Vector2 contactPoint;
    Vector2 contactNormal;
    Vector2 contactTime;
    class ColliderComponent* other;
};

class ColliderComponent : public Component {
public:
    ColliderComponent(class Actor* owner);
    ~ColliderComponent();

    virtual Manifold Intersects(ColliderComponent* other, float deltaTime) = 0;
    virtual void ResolveOverlap(const Manifold& manifold) = 0;

    CollisionLayer GetLayer() const { return layer; }
    void SetLayer(CollisionLayer layer) { this->layer = layer; }

    class RigidbodyComponent* GetAttachedRigidbody() const;
private:
    CollisionLayer layer;
};
