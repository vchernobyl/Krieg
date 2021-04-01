#pragma once

#include "ColliderComponent.h"
#include "Math.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner);
    ~BoxColliderComponent();
    
    Manifold Intersects(ColliderComponent* other) override;
    void ResolveOverlap(const Manifold& manifold) override;

    void SetCollidable(const Rect& rect);
    const Rect& GetCollidable();
private:
    void SetPosition();
    Rect rect;
    Vector2 offset;
};
