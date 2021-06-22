#pragma once

#include <vector>
#include <memory>

class PhysicsWorld {
public:
    PhysicsWorld(const class Vector2& gravity);
    void Shutdown();
    
    void Step(float timeStep);

    void AddCollider(class ColliderComponent* collider);
    void RemoveCollider(class ColliderComponent* collider);

    void AddRigidbody(class RigidbodyComponent* rigidbody);
    void RemoveRigidbody(class RigidbodyComponent* rigidbody);
private:
    friend class RigidbodyComponent;
    
    std::vector<class ColliderComponent*> colliders;
    std::vector<class RigidbodyComponent*> rigidbodies;

    class Box2DDebugRenderer* debugRenderer;
    class b2World* world;
};
