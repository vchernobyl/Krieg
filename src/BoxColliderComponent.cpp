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
    
    info.colliding = minkowski.Contains(Vector2::Zero);

    Vector2 point = Vector2::Zero;
    Vector2 min = minkowski.position;
    Vector2 max = minkowski.position + minkowski.size;

    float minDist = Math::Fabs(point.x - min.x);
    Vector2 boundsPoint = Vector2(min.x, point.y);

    if (Math::Fabs(max.x - point.x) < minDist) {
	minDist = Math::Fabs(max.x - point.x);
	boundsPoint = Vector2(max.x, point.y);
    } else if (Math::Fabs(max.y - point.y) < minDist) {
	minDist = Math::Fabs(max.y - point.y);
	boundsPoint = Vector2(point.x, max.y);
    } else if (Math::Fabs(min.y - point.y) < minDist) {
	minDist = Math::Fabs(min.y - point.y);
	boundsPoint = Vector2(point.x, min.y);
    }

    info.contactNormal = boundsPoint;

    return info;
}

void BoxColliderComponent::ResolveCollision(const CollisionInfo& info, float deltaTime) {
    auto rigidbody = GetAttachedRigidbody();
    auto resolution = -rigidbody->velocity + info.contactNormal;
    GetAttachedRigidbody()->velocity += resolution;
}

void BoxColliderComponent::Update(float deltaTime) {
    box.position = owner->GetPosition() + offset;
    box.size = size;
}
