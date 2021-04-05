#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "Collisions.h"
#include "BoxColliderComponent.h"
#include "SDL.h"
#include <algorithm>
#include <vector>

void PhysicsWorld::Update(float deltaTime) {
    std::vector<Manifold> toResolve;

    if (colliders.size() == 0) return;

    const auto player = dynamic_cast<BoxColliderComponent*>(colliders.front());
    auto& playerRect = player->GetCollidable();
    
    for (auto i = colliders.begin() + 1; i != colliders.end(); i++) {
	auto manifold = player->Intersects(*i, deltaTime);
	if (manifold.colliding) {
	    SDL_Log("player is colliding");
	    toResolve.push_back(manifold);
	} else {
	    SDL_Log("player is not colliding");
	}
    }

    std::sort(toResolve.begin(), toResolve.end(), [](const Manifold& a, const Manifold& b) {
	return a.contactTime < b.contactTime;
    });

    for (auto& manifold : toResolve) {
	if (DynamicRectsIntersect(playerRect, *manifold.other, manifold.contactPoint, manifold.contactNormal, manifold.contactTime, deltaTime)) {
	    playerRect.velocity += manifold.contactNormal * Vector2(Math::Fabs(playerRect.velocity.x), Math::Fabs(playerRect.velocity.y)) * (1.0f - manifold.contactTime);
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
