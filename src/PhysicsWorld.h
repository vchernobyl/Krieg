#pragma once

#include <vector>

class PhysicsWorld {
public:
    void Update(float deltaTime);
    void AddCollider(class ColliderComponent* collider);
    void RemoveCollider(class ColliderComponent* collider);
    const std::vector<class ColliderComponent*>& GetColliders() const { return colliders; }
private:
    std::vector<class ColliderComponent*> colliders;
};
