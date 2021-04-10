#include "PhysicsWorld.h"
#include "Collisions.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Actor.h"
#include <algorithm>
#include <vector>

void PhysicsWorld::Update(float deltaTime) {
    std::vector<CollisionInfo> collisions;

    if (colliders.size() == 0) return;

    const auto playerCollider = dynamic_cast<BoxColliderComponent*>(colliders.front());
    
    for (auto i = colliders.begin() + 1; i != colliders.end(); i++) {
	auto info = playerCollider->Intersects(*i, deltaTime);
	if (info.colliding) {
	    collisions.push_back(info);
	}
    }

    std::sort(collisions.begin(), collisions.end(), [](const CollisionInfo& a, const CollisionInfo& b) {
	return a.contactTime < b.contactTime;
    });

    for (auto& info : collisions) {
	auto rigidbody = playerCollider->GetAttachedRigidbody();
	auto otherCollider = dynamic_cast<BoxColliderComponent*>(info.other);
	if (BoxCollidersIntersect(playerCollider, otherCollider, info, deltaTime)) {
	    rigidbody->velocity += info.contactNormal
		* Vector2(Math::Fabs(rigidbody->velocity.x), Math::Fabs(rigidbody->velocity.y))
		* (1.0f - info.contactTime);
	}
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
