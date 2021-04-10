#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Collisions.h"
#include "Actor.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner) : ColliderComponent(owner) {}

BoxColliderComponent::~BoxColliderComponent() {}

CollisionInfo BoxColliderComponent::Intersects(ColliderComponent* other, float deltaTime) {
    CollisionInfo info;
    if (auto boxCollider = dynamic_cast<BoxColliderComponent*>(other)) {
	if (BoxCollidersIntersect(this, boxCollider, info, deltaTime)) {
	    info.colliding = true;
	    info.other = other;
	}
    }
    return info;
}

void BoxColliderComponent::ResolveCollision(const CollisionInfo& info) {
    // TODO: Resolve collision with other box collider here. Apply velocity to this collider's
    // rigidbody. If not static.
    if (owner->IsStatic()) return;
}

Rect& BoxColliderComponent::GetBox() {
    box.position = owner->GetPosition() + offset;
    box.size = size;
    return box;
}
