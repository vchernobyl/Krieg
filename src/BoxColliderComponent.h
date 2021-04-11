#pragma once

#include "ColliderComponent.h"
#include "Math.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(Actor* owner);
    ~BoxColliderComponent();
    
    CollisionInfo Intersects(ColliderComponent* other, float deltaTime) override;
    void ResolveCollision(const CollisionInfo& info) override;

    void SetOffset(Vector2 offset) { this->offset = offset; }
    void SetSize(Vector2 size) { this->size = size; }
    Rect& GetBox();
private:
    Vector2 offset;
    Vector2 size;
    Rect box;
};

bool RayIntersects(const Vector2& rayOrigin, const Vector2& rayDir, const Rect& target,
		   Vector2& contactPoint, Vector2& contactNormal, float& tHitNear);

bool BoxCollidersIntersect(class BoxColliderComponent* a, class BoxColliderComponent* b,
			   class CollisionInfo& info, float deltaTime);
