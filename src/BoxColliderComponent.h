#pragma once

#include "ColliderComponent.h"
#include "Collision.h"
#include "Math.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(Actor* owner);
    ~BoxColliderComponent();
    
    CollisionInfo Intersects(ColliderComponent* other, float deltaTime) override;
    void ResolveCollision(const CollisionInfo& info) override;

    AABB& GetBox() { return box; }
    void SetBox(const AABB& box) { this->box = box; }
private:
    AABB box;
};
