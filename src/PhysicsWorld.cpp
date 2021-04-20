#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include <algorithm>

const float Gravity = 9.81f;

void PhysicsWorld::Update(float deltaTime) {
    if (colliders.size() == 0) return;

    for (auto rb : rigidbodies) {
	if (rb->IsDynamic()) {
	    rb->velocity.y += (Gravity * deltaTime);
	}
    }

    for (auto i = colliders.begin(); i != colliders.end(); i++) {
	for (auto j = colliders.begin(); j != colliders.end(); j++) {
	    if (i == j) continue;
	    auto info = (*i)->Intersects(*j);
	    if (info.colliding) {
		activeCollisions.push_back(info);
	    }
	}
    }

    std::sort(activeCollisions.begin(), activeCollisions.end(), [](const CollisionInfo& a, const CollisionInfo& b) {
	return a.contactTime < b.contactTime;
    });

    for (auto& info : activeCollisions) {
	auto other = dynamic_cast<BoxColliderComponent*>(info.other);
	auto current = dynamic_cast<BoxColliderComponent*>(info.current);
	if (BoxCollidersIntersect(current, other, info)) {
	    current->ResolveCollision(info);
	}
    }

    activeCollisions.clear();
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
