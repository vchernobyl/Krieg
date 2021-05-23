#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Actor.h"
#include "Debug.h"

#include <algorithm>
#include <cmath>
#include <cassert>

BoxColliderComponent::BoxColliderComponent(Actor* owner) : ColliderComponent(owner) {}

BoxColliderComponent::~BoxColliderComponent() {}

CollisionInfo BoxColliderComponent::Intersects(ColliderComponent* other) {
    CollisionInfo info;

    auto otherBox = dynamic_cast<BoxColliderComponent*>(other)->GetBox();

    auto topLeft = otherBox.position - (box.position + box.size);
    auto fullSize = box.size + otherBox.size;
    auto minkowski = Rectangle(topLeft, fullSize);

    Debug::DrawRect(box);
    Debug::DrawRect(otherBox);
    
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
    }

    return info;
}

void BoxColliderComponent::ResolveCollision(const CollisionInfo& info) {
    auto rigidbody = GetAttachedRigidbody();
    if (!rigidbody->isKinematic) {
	auto resolution = info.penetrationVector;
	rigidbody->velocity += info.penetrationVector;
    }
}

void BoxColliderComponent::Update(float deltaTime) {
    box.position = owner->GetPosition() + offset;
    box.size = size;
}
