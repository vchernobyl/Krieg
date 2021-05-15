#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Actor.h"

#include <algorithm>
#include <cassert>

const float Gravity = 9.81f;

void PhysicsWorld::Update(float deltaTime) {
    assert(colliders.size() == rigidbodies.size());

    for (auto rb : rigidbodies) {
	if (!rb->isKinematic) {
	    rb->velocity.y += (Gravity * deltaTime);
	}
    }

    for (auto i = colliders.begin(); i != colliders.end(); i++) {
	for (auto j = colliders.begin(); j != colliders.end(); j++) {
	    if (i == j) continue;
	    // PERF: get rid of the casts here, very expensive
	    auto currentBox = dynamic_cast<BoxColliderComponent*>(*i);
	    auto otherBox = dynamic_cast<BoxColliderComponent*>(*j);
	    auto info = currentBox->Intersects(otherBox);

	    if (!info.colliding) continue;

	    if (otherBox->isTrigger) {
		currentBox->GetOwner()->OnTriggerEnter(info);
	    } else {
		collisionToResolve.push_back(info);
	    }
	}
    }

    std::sort(collisionToResolve.begin(), collisionToResolve.end(), [](const CollisionInfo& a, const CollisionInfo& b) {
	return a.contactTime < b.contactTime;
    });

    for (auto& info : collisionToResolve) {
	// PERF: get rid of the casts here, very expensive
	auto other = dynamic_cast<BoxColliderComponent*>(info.other);
	auto current = dynamic_cast<BoxColliderComponent*>(info.current);
	if (BoxCollidersIntersect(current, other, info)) {
	    current->GetOwner()->OnCollisionEnter(info);
	    current->ResolveCollision(info);
	}
    }

    collisionToResolve.clear();
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
