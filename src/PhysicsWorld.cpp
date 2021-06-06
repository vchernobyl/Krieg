#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "Actor.h"
#include "Debug.h"

#include <algorithm>
#include <cassert>

const float Gravity = 9.81f;

void PhysicsWorld::Step(float deltaTime) {
    // Update collider positions to match that of the actors.
    for (auto collider : colliders) {
	const auto owner = collider->GetOwner();
	const auto box = dynamic_cast<BoxColliderComponent*>(collider);

	auto& aabb = box->GetBox();
	aabb.UpdateMinMax(owner->GetPosition());
    }

    // Match actor position to that of the rigidbodies.
    for (auto rb : rigidbodies) {
	if (rb->GetMotionType() != MotionType::Fixed) {
	    rb->GetOwner()->Translate(rb->velocity);
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
		SDL_Log("colliding");
		first->ResolveCollision(info);
	    } else {
		SDL_Log("not colliding");
	    }
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
