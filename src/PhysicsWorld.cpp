#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Player.h"
#include "Actor.h"
#include "Debug.h"

#include <algorithm>
#include <cassert>

const float Gravity = 9.81f;

void PhysicsWorld::Step(float deltaTime) {
    // Apply forces to the physics driven rigidbodies.
    for (auto rb : rigidbodies) {
	if (rb->GetMotionType() == MotionType::PhysicsDriven) {
	    rb->velocity.y += Gravity * deltaTime;
	}
    }

    
    // Advance the game objects base on their velocity.
    for (auto rb : rigidbodies) {
	if (rb->GetMotionType() != MotionType::Fixed) {
	    rb->GetOwner()->Translate(rb->velocity);
	}
    }

    // Update collider positions to match that of the actors.
    // TODO: Could be possibly merged with the previous step.
    // It would be nice to have a handle to the collider from the rigidbody.
    for (auto collider : colliders) {
	const auto owner = collider->GetOwner();
	const auto box = dynamic_cast<BoxColliderComponent*>(collider);
	auto& aabb = box->GetBox();
	aabb.UpdateMinMax(owner->GetPosition());
    }

    // Detect and resolve collisions of non-fixed rigidbodies.
    for (auto i = colliders.begin(); i != colliders.end(); i++) {
	auto first = *i;
	const auto rigidbody = first->GetAttachedRigidbody();
	
	for (auto j = colliders.begin(); j != colliders.end(); j++) {
	    // TODO: Optimize loop. A vs B and B vs A collision check is not necessary.
	    if (i == j) continue;

	    auto second = *j;

	    if (rigidbody->GetMotionType() != MotionType::Fixed) {
		const auto info = first->Intersects(second, deltaTime);
		if (info.colliding) {
		    first->ResolveCollision(info);
		}
	    }
	}
    }

    // Draw collision boxes after collisions have been resolved, they will now
    // match the positions of the owning actors perfectly.
    for (auto collider : colliders) {
	const auto box = dynamic_cast<BoxColliderComponent*>(collider);
	const auto& aabb = box->GetBox();
	Debug::DrawRect(Rectangle(aabb.min, aabb.max - aabb.min));
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
