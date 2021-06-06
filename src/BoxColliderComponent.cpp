#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Actor.h"
#include "Debug.h"
#include "Game.h"
#include "Renderer.h"
#include "Camera.h"
#include "Player.h"

#include <cassert>

BoxColliderComponent::BoxColliderComponent(Actor* owner) : ColliderComponent(owner) {}

BoxColliderComponent::~BoxColliderComponent() {}

CollisionInfo BoxColliderComponent::Intersects(ColliderComponent* other, float deltaTime) {
    CollisionInfo info;

    const auto otherCollider = dynamic_cast<BoxColliderComponent*>(other);
    const auto minkowski = MinkowskiDifference(box, otherCollider->GetBox());

    Debug::DrawRect(box);
    Debug::DrawRect(otherCollider->GetBox());

    assert(box.position == GetOwner()->GetPosition());

    if (minkowski.Contains(Vector2::Zero)) {
	info.colliding = true;
	
	const auto origin = Vector2::Zero;
	const auto min = minkowski.position;
	const auto max = minkowski.position + minkowski.size;
	
	auto minDist = Math::Fabs(origin.x - min.x);
	auto closestPoint = Vector2(min.x, origin.y);

	if (Math::Fabs(max.x - origin.x) < minDist) {
	    minDist = Math::Fabs(max.x - origin.x);
	    closestPoint = Vector2(max.x, origin.y);
	}
	if (Math::Fabs(max.y - origin.y) < minDist) {
	    minDist = Math::Fabs(max.y - origin.y);
	    closestPoint = Vector2(origin.x, max.y);
	}
	if (Math::Fabs(min.y - origin.y) < minDist) {
	    minDist = Math::Fabs(min.y - origin.y);
	    closestPoint = Vector2(origin.x, min.y);
	}

	info.penetration = closestPoint;
	info.normal = Vector2::Normalize(closestPoint);
    }

    return info;
}

void BoxColliderComponent::ResolveCollision(const CollisionInfo& info) {
    auto rigidbody = GetAttachedRigidbody();
    rigidbody->position += info.penetration;

    const auto normal = info.normal;
    if (normal != Vector2::Zero) {
	rigidbody->velocity -= normal * Vector2::Dot(rigidbody->velocity, normal);
    }
}

// TODO: Rethink this approach. It is very bad, because positions are updated outside of the dynamics
// simulation. Ideally, these should be somewhere in the physics step.
void BoxColliderComponent::Update(float deltaTime) {
    box.position = owner->GetPosition() + offset;
    box.size = size;
}
