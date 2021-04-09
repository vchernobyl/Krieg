#include "PhysicsWorld.h"
#include "Collisions.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Actor.h"
#include <algorithm>
#include <vector>

void PhysicsWorld::Update(float deltaTime) {
    std::vector<Manifold> collisions;

    if (colliders.size() == 0) return;

    const auto playerCollider = dynamic_cast<BoxColliderComponent*>(colliders.front());
    
    for (auto i = colliders.begin() + 1; i != colliders.end(); i++) {
	auto manifold = playerCollider->Intersects(*i, deltaTime);
	if (manifold.colliding) {
	    collisions.push_back(manifold);
	}
    }

    std::sort(collisions.begin(), collisions.end(), [](const Manifold& a, const Manifold& b) {
	return a.contactTime < b.contactTime;
    });

    for (auto& manifold : collisions) {
	auto rigidbody = playerCollider->GetAttachedRigidbody();
	rigidbody->velocity += manifold.contactNormal
	    * Vector2(Math::Fabs(rigidbody->velocity.x), Math::Fabs(rigidbody->velocity.y))
	    * (1.0f - manifold.contactTime);
    }
}

void PhysicsWorld::AddCollider(ColliderComponent* collider) {
    colliders.push_back(collider);
}

void PhysicsWorld::RemoveCollider(ColliderComponent* collider) {
    auto iter = std::find(colliders.begin(), colliders.end(), collider);
    if (iter != colliders.end()) {
	std::iter_swap(iter, colliders.end() - 1);
	colliders.pop_back();
    }
}

void PhysicsWorld::AddRigidbody(RigidbodyComponent* rigidbody) {
    rigidbodies.push_back(rigidbody);
}

void PhysicsWorld::RemoveRigidbody(RigidbodyComponent* rigidbody) {
    auto iter = std::find(rigidbodies.begin(), rigidbodies.end(), rigidbody);
    if (iter != rigidbodies.end()) {
	std::iter_swap(iter, rigidbodies.end() - 1);
	rigidbodies.pop_back();
    }
}
