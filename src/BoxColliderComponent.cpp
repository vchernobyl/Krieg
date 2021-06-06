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
    CollisionInfo info;

    const auto otherCollider = dynamic_cast<BoxColliderComponent*>(other);
    const auto minkowski = MinkowskiDifference(otherCollider->GetBox(), box);

    // This draw is lagging behind by one frame, because box's position matches actor's,
    // who hasn't been translated by the velocity, which is the last step.
    // auto debugBox = box;
    // debugBox.UpdateMinMax(GetOwner()->GetPosition() + GetAttachedRigidbody()->velocity);
    // Debug::DrawRect(Rectangle(debugBox.min, debugBox.max - debugBox.min));
    Debug::DrawRect(Rectangle(box.min, box.max - box.min));

    const auto otherBox = otherCollider->GetBox();
    Debug::DrawRect(Rectangle(otherBox.min, otherBox.max - otherBox.min));

    // TODO: Extract!
    if (minkowski.min.x <= 0 && minkowski.max.x >= 0 &&
	minkowski.min.y <= 0 && minkowski.max.y >= 0) {
	info.colliding = true;
	
	const auto penetration = minkowski.ClosestPointOnEdge(Vector2::Zero);

	info.penetration = penetration;
	info.normal = Vector2::Normalize(penetration);
	info.other = other;
    }

    return info;
}

void BoxColliderComponent::ResolveCollision(const CollisionInfo& info) {
    GetOwner()->Translate(info.penetration);

    const auto normal = info.normal;
    if (normal != Vector2::Zero) {
	auto rigidbody = GetAttachedRigidbody();
	rigidbody->velocity -= normal * Vector2::Dot(rigidbody->velocity, normal);
    }
}
