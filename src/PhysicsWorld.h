#pragma once

#include <vector>

class PhysicsWorld {
public:
    void Update(float deltaTime);

    void AddCollider(class ColliderComponent* collider);
    void RemoveCollider(class ColliderComponent* collider);
    const std::vector<class ColliderComponent*>& GetColliders() const { return colliders; }

    void AddRigidbody(class RigidbodyComponent* rigidbody);
    void RemoveRigidbody(class RigidbodyComponent* rigidbody);
    const std::vector<class RigidbodyComponent*>& GetRigidbodies() const { return rigidbodies; }

private:
    std::vector<class ColliderComponent*> colliders;
    std::vector<class RigidbodyComponent*> rigidbodies;
    std::vector<struct CollisionInfo> activeCollisions;
};
