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
    auto otherBox = otherCollider->GetBox();

    auto topLeft = otherBox.position - (box.position + box.size);
    auto fullSize = box.size + otherBox.size;
    auto minkowski = Rectangle(topLeft, fullSize);

    Debug::DrawRect(box);
    Debug::DrawRect(otherBox);

    // Minkowi debug
    auto minkowskiDebug = minkowski;
    auto camera= GetOwner()->GetGame()->GetRenderer()->GetCamera();
    auto cameraPos = camera->GetPosition();
    cameraPos += camera->GetViewportSize() / 2;
    minkowskiDebug.position += cameraPos;

    auto originRect = Rectangle(cameraPos, Vector2(1, 1));
    Debug::DrawRect(minkowskiDebug);
    Debug::DrawRect(originRect);
    
    if (minkowski.Contains(Vector2::Zero)) {
	// info.colliding = true;
	
	// auto origin = Vector2::Zero;
	// auto min = minkowski.position;
	// auto max = minkowski.position + minkowski.size;

	// auto minDist = Math::Fabs(origin.x - min.x);
	// auto closestPoint = Vector2(min.x, origin.y);

	// if (Math::Fabs(max.x - origin.x) < minDist) {
	//     minDist = Math::Fabs(max.x - origin.x);
	//     closestPoint = Vector2(max.x, origin.y);
	// }
	// if (Math::Fabs(max.y - origin.y) < minDist) {
	//     minDist = Math::Fabs(max.y - origin.y);
	//     closestPoint = Vector2(origin.x, max.y);
	// }
	// if (Math::Fabs(min.y - origin.y) < minDist) {
	//     minDist = Math::Fabs(min.y - origin.y);
	//     closestPoint = Vector2(origin.x, min.y);
	// }

	// info.penetrationVector = closestPoint;
	// auto rigidbody = GetAttachedRigidbody();
	// if (!rigidbody->isKinematic) {
	//     GetOwner()->Translate(info.penetrationVector);

	//     if (info.penetrationVector != Vector2::Zero) {
	// 	auto tan = Vector2::Tan(info.penetrationVector.Normalized());
	// 	auto aRigidbody = GetAttachedRigidbody();
	// 	auto bRigidbody = otherCollider->GetAttachedRigidbody();
	// 	aRigidbody->velocity = Vector2::Dot(aRigidbody->velocity, tan) * tan;
	// 	bRigidbody->velocity = Vector2::Dot(bRigidbody->velocity, tan) * tan;
	//     }
	// }
    } else {
	auto velocity = GetAttachedRigidbody()->velocity;
	auto otherVelocity = otherCollider->GetAttachedRigidbody()->velocity;
	auto relativeVelocity = velocity;


	Vector2 normal;
	auto t = minkowski.RayIntersectionTime(Vector2::Zero, relativeVelocity, normal);

	Debug::DrawLine(originRect.position, originRect.position + relativeVelocity);

	if (t < Math::Infinity) {	    
	    GetOwner()->Translate(velocity * t);
	    
	    auto norm = Vector2::Normalize(relativeVelocity);
	    SDL_Log("norm.x=%f, norm.y=%f", norm.x, norm.y);

	    auto tangent = Vector2(-norm.y, norm.x);
	    auto v1 = Vector2::Dot(velocity, tangent) * tangent;
	    
	    GetAttachedRigidbody()->velocity = v1;
	} else {
	    GetOwner()->Translate(GetAttachedRigidbody()->velocity);
	    otherCollider->GetOwner()->Translate(otherCollider->GetAttachedRigidbody()->velocity);
	}
    }

    return info;
}

void BoxColliderComponent::ResolveCollision(const CollisionInfo& info) {
    // auto rigidbody = GetAttachedRigidbody();
    // if (!rigidbody->isKinematic) {
    // 	auto resolution = info.penetrationVector;
    // 	rigidbody->velocity += info.penetrationVector;
    // }
}

void BoxColliderComponent::Update(float deltaTime) {
    box.position = owner->GetPosition() + offset;
    box.size = size;
}
