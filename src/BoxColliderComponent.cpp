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
    if (owner->IsStatic()) return;

    auto rigidbody = GetAttachedRigidbody();
    rigidbody->velocity += info.contactNormal
	* Vector2(Math::Fabs(rigidbody->velocity.x), Math::Fabs(rigidbody->velocity.y))
	* (1.0f - info.contactTime);
}

Rect& BoxColliderComponent::GetBox() {
    box.position = owner->GetPosition() + offset;
    box.size = size;
    return box;
}
