#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "BoxColliderComponent.h"
#include "SDL.h"
#include <algorithm>

void PhysicsWorld::Update(float deltaTime) {
    for (auto i = colliders.begin(); i != colliders.end(); ++i) {
	for (auto j = i + 1; j != colliders.end(); ++j) {
	    auto manifold = (*i)->Intersects(*j);
	    if (manifold.colliding) {
		(*i)->ResolveOverlap(manifold);
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
