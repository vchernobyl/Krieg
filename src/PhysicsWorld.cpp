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
    assert(collisionToResolve.empty());
    
    for (auto rb : rigidbodies) {
	if (!rb->isKinematic) {
//	    rb->velocity.y += (Gravity * deltaTime);
	}
    }

    for (auto i = colliders.begin(); i != colliders.end(); i++) {
	for (auto j = i + 1; j != colliders.end(); j++) {
	    if (i == j) continue;
	    auto current = *i;
	    auto other = *j;
	    auto info = current->Intersects(other, deltaTime);
	    // if (info.colliding) {
	    // 	current->GetOwner()->OnCollisionEnter(info);
	    // 	other->GetOwner()->OnCollisionEnter(info);
	    // 	current->ResolveCollision(info);
	    // }
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
