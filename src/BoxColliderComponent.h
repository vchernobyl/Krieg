#pragma once

#include "ColliderComponent.h"
#include "Math.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(Actor* owner);
    ~BoxColliderComponent();
    
    CollisionInfo Intersects(ColliderComponent* other, float deltaTime) override;
    void ResolveCollision(const CollisionInfo& info) override;
    void Update(float deltaTime) override;

    void SetOffset(const Vector2& offset) { this->offset = offset; }
    void SetSize(const Vector2& size) { this->size = size; }
    
    void SetBoxPosition(const Vector2& position) { this->box.position = position; }
    Vector2 GetBoxPosition() const { return box.position; }

    Rectangle& GetBox() { return box; }
private:
    Vector2 offset;
    Vector2 size;
    Rectangle box;
};
