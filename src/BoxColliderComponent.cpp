#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Collisions.h"
#include "Actor.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner)
    : ColliderComponent(owner) {}

BoxColliderComponent::~BoxColliderComponent() {}

Manifold BoxColliderComponent::Intersects(ColliderComponent* other, float deltaTime) {
    Manifold manifold;
    if (auto boxCollider = dynamic_cast<BoxColliderComponent*>(other)) {
	if (BoxCollidersIntersect(this, boxCollider, manifold, deltaTime)) {
	    manifold.colliding = true;
	    manifold.other = &(boxCollider->GetCollidable());
	}
    }
    return manifold;
}

void BoxColliderComponent::ResolveOverlap(const Manifold& manifold) {
    if (owner->IsStatic()) return;
}

void BoxColliderComponent::SetCollidable(Rect rect) {
    this->rect = rect;
    this->offset.x = rect.position.x;
    this->offset.y = rect.position.y;
    SetPosition();
}

Rect& BoxColliderComponent::GetCollidable() {
    SetPosition();
    return rect;
}

void BoxColliderComponent::SetPosition() {
    const auto& pos = owner->GetPosition();
    rect.position.x = pos.x + offset.x;
    rect.position.y = pos.y + offset.y;
}
