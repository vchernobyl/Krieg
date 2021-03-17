#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner)
    : ColliderComponent(owner) {}

Manifold BoxColliderComponent::Intersects(ColliderComponent* other) {
    Manifold info;
    if (auto boxCollider = dynamic_cast<BoxColliderComponent*>(other)) {
	const auto& rect1 = GetCollidable();
	const auto& rect2 = boxCollider->GetCollidable();
	if (SDL_HasIntersection(&rect1, &rect2)) {
	    info.colliding = true;
	    info.other = &rect2;
	}
    }
    return info;
}

void BoxColliderComponent::ResolveOverlap(const Manifold& manifold) {
    if (owner->IsStatic()) { return; }
    const auto& rect1 = GetCollidable();
    const auto& rect2 = manifold.other;
}
