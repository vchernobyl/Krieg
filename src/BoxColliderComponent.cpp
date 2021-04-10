#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Collisions.h"
#include "Actor.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner) : ColliderComponent(owner) {}

BoxColliderComponent::~BoxColliderComponent() {}

Manifold BoxColliderComponent::Intersects(ColliderComponent* other, float deltaTime) {
    Manifold manifold;
    if (auto boxCollider = dynamic_cast<BoxColliderComponent*>(other)) {
	if (BoxCollidersIntersect(this, boxCollider, manifold, deltaTime)) {
	    manifold.colliding = true;
	    manifold.other = &(boxCollider->GetBox());
	}
    }
    return manifold;
}

void BoxColliderComponent::ResolveOverlap(const Manifold& manifold) {
    // TODO: Resolve collision with other box collider here. Apply velocity to this collider's
    // rigidbody. If not static.
    if (owner->IsStatic()) return;
}

Rect& BoxColliderComponent::GetBox() {
    box.position = owner->GetPosition() + offset;
    box.size = size;
    return box;
}
