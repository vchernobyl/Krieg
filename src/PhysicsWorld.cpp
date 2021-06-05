#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Actor.h"

#include <algorithm>
#include <cassert>

const float Gravity = 9.81f;

void PhysicsWorld::Step(float deltaTime) {
    // TODO: This shouldn't be the case anymore.
    // Actors can have a collider without a rigidbody (eg. Trigger/Phantom).
    assert(colliders.size() == rigidbodies.size());

    // Update rigidbody position to match that of the actors.
    for (auto rb : rigidbodies) {
	rb->position = rb->GetOwner()->GetPosition();
    }

    // Apply forces.
    for (auto rb : rigidbodies) {
	if (rb->GetMotionType() == MotionType::PhysicsDriven) {
	    rb->velocity.y += Gravity * deltaTime;
	}
    }
    
    // Detect and resolve collisions of non-fixed rigidbodies.
    for (auto i = colliders.begin(); i != colliders.end(); i++) {
	auto first = *i;
	for (auto j = i + 1; j != colliders.end(); j++) {
	    auto second = *j;
	    auto rigidbody = first->GetAttachedRigidbody();
	    if (rigidbody->GetMotionType() == MotionType::Fixed) continue;
	    
	    auto info = first->Intersects(second, deltaTime);
	    if (info.colliding) {
		first->ResolveCollision(info);
	    }
	}
    }

    int i = 0;
    // Match actor position to that of the rigidbodies.
    for (auto rb : rigidbodies) {
	if (rb->GetMotionType() != MotionType::Fixed) {
	    i++;
	    //SDL_Log("Actor #%d: v.x=%f, v.y=%f", i, rb->velocity.x, rb->velocity.y);
	    rb->position += rb->velocity;
	    rb->GetOwner()->SetPosition(rb->position);
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
