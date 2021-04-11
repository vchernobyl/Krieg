#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Actor.h"
#include <algorithm>
#include <vector>

void PhysicsWorld::Update(float deltaTime) {
    std::vector<CollisionInfo> collisions;

    if (colliders.size() == 0) return;

    // Gravity
    for (auto rb : rigidbodies) {
	rb->velocity.y += 9.81f;
    }

    const auto playerCollider = dynamic_cast<BoxColliderComponent*>(colliders.front());
    
    for (auto iter = colliders.begin() + 1; iter != colliders.end(); iter++) {
	auto info = playerCollider->Intersects(*iter, deltaTime);
	if (info.colliding) {
	    collisions.push_back(info);
	}
    }

    std::sort(collisions.begin(), collisions.end(), [](const CollisionInfo& a, const CollisionInfo& b) {
	return a.contactTime < b.contactTime;
    });

    for (auto& info : collisions) {
	auto otherCollider = dynamic_cast<BoxColliderComponent*>(info.other);
	if (BoxCollidersIntersect(playerCollider, otherCollider, info, deltaTime)) {
	    playerCollider->ResolveCollision(info);
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
