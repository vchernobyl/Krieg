#pragma once

#include <vector>

class PhysicsWorld {
public:
    void Update(float deltaTime);

    void AddCollider(class ColliderComponent* collider);
    void RemoveCollider(class ColliderComponent* collider);

    void AddRigidbody(class RigidbodyComponent* rigidbody);
    void RemoveRigidbody(class RigidbodyComponent* rigidbody);
private:
    std::vector<class ColliderComponent*> colliders;
    std::vector<class RigidbodyComponent*> rigidbodies;
};
