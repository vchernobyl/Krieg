#pragma once

#include <vector>

class PhysicsWorld {
public:
    PhysicsWorld();
    void AddCollider(class ColliderComponent* collider);
    void RemoveCollider(class ColliderComponent* collider);
private:
    std::vector<class ColliderComponent*> colliders;
};
