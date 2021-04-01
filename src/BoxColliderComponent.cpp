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
	if (rect1.Intersects(rect2)) {
	    manifold.colliding = true;
	    manifold.other = &rect2;
	}
    }
    return manifold;
}

void BoxColliderComponent::ResolveOverlap(const Manifold& manifold) {
    if (owner->IsStatic()) return;
}

void BoxColliderComponent::SetCollidable(const Rect& rect) {
    this->rect = rect;
    this->offset.x = rect.position.x;
    this->offset.y = rect.position.y;
    SetPosition();
}

const Rect& BoxColliderComponent::GetCollidable() {
    SetPosition();
    return rect;
}

void BoxColliderComponent::SetPosition() {
    const auto& pos = owner->GetPosition();
    rect.position.x = pos.x + offset.x;
    rect.position.y = pos.y + offset.y;
}
