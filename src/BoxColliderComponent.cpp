#include "BoxColliderComponent.h"
#include "Actor.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner)
    : ColliderComponent(owner), offset(Vector2::Zero) {}

BoxColliderComponent::~BoxColliderComponent() {}

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

    const auto& own = GetCollidable();
    const auto other = manifold.other;

    float resolve = 0;
    const float xDiff = (own.x + (own.w * 0.5f)) - (other->x + (other->w * 0.5f));
    const float yDiff = (own.y + (own.h * 0.5f)) - (other->y + (other->h * 0.5f));

    if (Math::Fabs(xDiff) > Math::Fabs(yDiff)) {
	if (xDiff > 0) {
	    // Colliding from the left, move this object to the right.
	    resolve = (other->x + other->w) - own.x;
	} else {
	    // Colliding from the right, move this object to the left.
	    resolve = -((own.x + own.w) - other->x);
	}
	owner->Translate(resolve, 0);
    } else {
	if (yDiff > 0) {
	    // Colliding from the top, move this object down.
	    resolve = (other->y + other->h) - own.y;
	} else {
	    // Colliding from the bottom, move this object up.
	    resolve = -((own.y + own.h) - other->y);
	}
	owner->Translate(0, resolve);
    }
}

void BoxColliderComponent::SetCollidable(const SDL_Rect& collidable) {
    this->collidable = collidable;
    this->offset.x = collidable.x;
    this->offset.y = collidable.y;
    SetPosition();
}

const SDL_Rect& BoxColliderComponent::GetCollidable() {
    SetPosition();
    return collidable;
}

void BoxColliderComponent::SetPosition() {
    const auto& pos = owner->GetPosition();
    collidable.x = pos.x + offset.x;
    collidable.y = pos.y + offset.y;
}
