#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Actor.h"
#include "Debug.h"
#include "Game.h"
#include "Renderer.h"
#include "Camera.h"
#include "Player.h"

#include <cassert>

BoxColliderComponent::BoxColliderComponent(Actor* owner)
    : ColliderComponent(owner),
      box(Vector2::Zero, Vector2::Zero) {}

BoxColliderComponent::~BoxColliderComponent() {}

CollisionInfo BoxColliderComponent::Intersects(ColliderComponent* other, float deltaTime) {
    assert(box.min == GetOwner()->GetPosition());

    CollisionInfo info;

    const auto otherCollider = dynamic_cast<BoxColliderComponent*>(other);
    const auto minkowski = MinkowskiDifference(otherCollider->GetBox(), box);

    // TODO: Maybe extract?
    if (minkowski.min.x <= 0 && minkowski.max.x >= 0 &&
	minkowski.min.y <= 0 && minkowski.max.y >= 0) {
	info.colliding = true;

	// TODO: Maybe inline?
	const auto penetration = minkowski.ClosestPointOnEdge(Vector2::Zero);

	info.penetration = penetration;
	info.normal = Vector2::Normalize(penetration);
    }

    return info;
}

void BoxColliderComponent::ResolveCollision(const CollisionInfo& info) {
    GetOwner()->Translate(info.penetration);
    box.UpdateMinMax(GetOwner()->GetPosition());

    const auto normal = info.normal;
    if (normal != Vector2::Zero) {
	auto rigidbody = GetAttachedRigidbody();
	rigidbody->velocity -= normal * Vector2::Dot(rigidbody->velocity, normal);
    }
}
