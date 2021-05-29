#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Actor.h"
#include "Debug.h"

#include "Game.h"
#include "Renderer.h"
#include "Camera.h"

#include <algorithm>
#include <cmath>
#include <cassert>

BoxColliderComponent::BoxColliderComponent(Actor* owner) : ColliderComponent(owner) {}

BoxColliderComponent::~BoxColliderComponent() {}

CollisionInfo BoxColliderComponent::Intersects(ColliderComponent* other, float deltaTime) {
    CollisionInfo info;

    auto otherCollider = dynamic_cast<BoxColliderComponent*>(other);
    auto minkowski = MinkowskiDifference(box, otherCollider->GetBox());

    Debug::DrawRect(box);
    Debug::DrawRect(otherCollider->GetBox());

    if (minkowski.Contains(Vector2::Zero)) {
	info.colliding = true;
	
	auto origin = Vector2::Zero;
	auto min = minkowski.position;
	auto max = minkowski.position + minkowski.size;

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

	info.penetrationVector = closestPoint;
	auto rigidbody = GetAttachedRigidbody();
	if (!rigidbody->isKinematic) {
	    // BUG: Fix the bounciness!
	    rigidbody->velocity += info.penetrationVector;
	}

	// } else {
    // 	auto velocity = GetAttachedRigidbody()->velocity;
    // 	auto otherVelocity = otherCollider->GetAttachedRigidbody()->velocity;
    // 	auto relativeVelocity = velocity - otherVelocity;

    // 	Vector2 normal;
    // 	auto t = minkowski.RayIntersectionTime(Vector2::Zero, relativeVelocity, normal);

    // 	//Debug::DrawLine(originRect.position, originRect.position + relativeVelocity);

    // 	if (t < Math::Infinity) {	    
    // 	    GetOwner()->Translate(velocity * (t - 0.001f));
    // 	    otherCollider->GetOwner()->Translate(otherVelocity * (t - 0.001f));

    // 	    auto tangent = Vector2(Math::Fabs(normal.y), Math::Fabs(normal.x));
    // 	    GetAttachedRigidbody()->velocity = tangent * velocity;
    // 	    otherCollider->GetAttachedRigidbody()->velocity = tangent * otherVelocity;
    // 	}
     }

    return info;
}

void BoxColliderComponent::ResolveCollision(const CollisionInfo& info) {
}

void BoxColliderComponent::Update(float deltaTime) {
    box.position = owner->GetPosition() + offset;
    box.size = size;
}
