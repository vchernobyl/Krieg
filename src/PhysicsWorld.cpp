#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "SDL.h"
#include <algorithm>

PhysicsWorld::PhysicsWorld() {}

void PhysicsWorld::AddCollider(ColliderComponent* collider) {
    colliders.push_back(collider);
    SDL_Log("Adding collider %p", collider);
}

//BUG: Currently collider is not being removed if physics world
// contains only one collider. It removed ALL colliders if it's more than one.
void PhysicsWorld::RemoveCollider(ColliderComponent* collider) {
    SDL_Log("collider count before removal: %d", colliders.size());
    auto iter = std::find(colliders.begin(), colliders.end(), collider);
    SDL_Log("Trying to remove a collider %p", collider);
    if (iter != colliders.end()) {
	std::iter_swap(iter, colliders.end() - 1);
	colliders.pop_back();
	SDL_Log("Removed collider");
    }
    SDL_Log("collider count after removal: %d", colliders.size());
}
