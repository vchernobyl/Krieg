#pragma once

#include "ColliderComponent.h"
#include "Math.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(Actor* owner);
    ~BoxColliderComponent();
    
    CollisionInfo Intersects(ColliderComponent* other) override;
    void ResolveCollision(const CollisionInfo& info, float deltaTime) override;
    void Update(float deltaTime) override;

    void SetOffset(Vector2 offset) { this->offset = offset; }
    void SetSize(Vector2 size) { this->size = size; }
    Rectangle& GetBox() { return box; }
private:
    Vector2 offset;
    Vector2 size;
    Rectangle box;
};
