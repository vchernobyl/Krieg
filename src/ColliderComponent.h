#pragma once

#include "Component.h"

enum class CollisionLayer {
    Default = 1,
    Player = 2,
    Tile = 3
};

struct Manifold {
    bool colliding = false;
    const class Rect* other;
};

class ColliderComponent : public Component {
public:
    ColliderComponent(class Actor* owner);
    ~ColliderComponent();

    virtual Manifold Intersects(ColliderComponent* other) = 0;
    virtual void ResolveOverlap(const Manifold& manifold) = 0;

    CollisionLayer GetLayer() const { return layer; }
    void SetLayer(CollisionLayer layer) { this->layer = layer; }
private:
    CollisionLayer layer;
};
