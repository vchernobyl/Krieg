#pragma once

#include "Component.h"
#include "Actor.h"

enum class CollisionLayer {
    Default = 1,
    Player = 2,
    Tile = 3
};

struct CollisionInfo {
    bool colliding = false;
    const SDL_Rect* other;
};

class ColliderComponent : public Component {
public:
    ColliderComponent(Actor* owner);
    ~ColliderComponent() {}

    virtual CollisionInfo Intersects(ColliderComponent* other) = 0;
    virtual void ResolveOverlap(const CollisionInfo& info) = 0;

    CollisionLayer GetLayer() const { return layer; }
    void SetLayer(CollisionLayer layer) { this->layer = layer; }
private:
    CollisionLayer layer;
};
