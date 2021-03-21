#include "BoxColliderComponent.h"
#include "Actor.h"
#include "Math.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner)
    : ColliderComponent(owner) {}

Manifold BoxColliderComponent::Intersects(ColliderComponent* other) {
    Manifold manifold;
    if (auto boxCollider = dynamic_cast<BoxColliderComponent*>(other)) {
	const auto& rect1 = GetCollidable();
	const auto& rect2 = boxCollider->GetCollidable();
	if (SDL_HasIntersection(&rect1, &rect2)) {
	    manifold.colliding = true;
	    manifold.other = &rect2;
	}
    }
    return manifold;
}

void BoxColliderComponent::ResolveOverlap(const Manifold& manifold) {
    if (owner->IsStatic()) { return; }
    const auto& rect1 = GetCollidable();
    const auto rect2 = manifold.other;

    float resolve = 0;
    float xDiff = (rect1.x + (rect1.w * 0.5f)) - (rect2->x + (rect2->w * 0.5f));
    float yDiff = (rect1.y + (rect1.h * 0.5f)) - (rect2->y + (rect2->h * 0.5f));

    if (Math::Fabs(xDiff) > Math::Fabs(yDiff)) {
	if (xDiff > 0) {
	    // Colliding from the left, move this object to the right.
	    resolve = (rect2->x + rect2->w) - rect1.x;
	    SDL_Log("Colliding from left, resolve = %f", resolve);
	} else {
	    // Colliding from the right, move this object to the left.
	    resolve = - ((rect1.x + rect1.w) - rect2->x);
	    SDL_Log("Colliding from right, resolve = %f", resolve);
	}
	owner->Translate(resolve, 0);
    } else {
	if (yDiff > 0) {
	    // Colliding from the top, move this object down.
	    resolve = (rect2->y + rect2->h) - rect1.y;
	    SDL_Log("Colliding from top, resolve = %f", resolve);
	} else {
	    // Colliding from the bottom, move this object up.
	    resolve = -((rect1.y + rect1.h) - rect2->y);
	    SDL_Log("Colliding from bottom, resolve = %f", resolve);
	}
	owner->Translate(0, resolve);
    }
}

void BoxColliderComponent::SetCollidable(const SDL_Rect& collidable) {
    this->collidable = collidable;
    SetPosition();
}

const SDL_Rect& BoxColliderComponent::GetCollidable() {
    SetPosition();
    return collidable;
}

void BoxColliderComponent::SetPosition() {
    const auto& pos = owner->GetPosition();
    collidable.x = pos.x - collidable.w / 2;
    collidable.y = pos.y - collidable.h / 2;
}
