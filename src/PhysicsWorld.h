#pragma once

#include <vector>
#include <b2_world.h>

class PhysicsWorld {
public:
    PhysicsWorld(const class Vector2& gravity);
    void Step(float timeStep);

    void AddCollider(class ColliderComponent* collider);
    void RemoveCollider(class ColliderComponent* collider);

    void AddRigidbody(class RigidbodyComponent* rigidbody);
    void RemoveRigidbody(class RigidbodyComponent* rigidbody);
private:
    friend class RigidbodyComponent;
    
    std::vector<class ColliderComponent*> colliders;
    std::vector<class RigidbodyComponent*> rigidbodies;

    b2World world;
};
