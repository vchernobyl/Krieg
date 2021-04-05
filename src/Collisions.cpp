#include "Collisions.h"
#include <algorithm>
#include <cmath>

bool RayIntersects(const Vector2& rayOrigin, const Vector2& rayDir, const Rect& target,
		   Vector2& contactPoint, Vector2& contactNormal, float& tHitNear) {
    Vector2 tNear = (target.position - rayOrigin) / rayDir;
    Vector2 tFar = (target.position + target.size - rayOrigin) / rayDir;

    if (std::isnan(tFar.y) || std::isnan(tFar.x)) return false;
    if (std::isnan(tNear.y) || std::isnan(tNear.x)) return false;
	
    if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
    if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);

    if (tNear.x > tFar.y || tNear.y > tFar.x) return false;

    // Replace min/max with the one from Math namespace
    tHitNear = std::max(tNear.x, tNear.y);
    float tHitFar = std::min(tFar.x, tFar.y);

    if (tHitFar < 0) return false;

    contactPoint = rayOrigin + tHitNear * rayDir;

    if (tNear.x > tNear.y) {
	if (rayDir.x < 0) {
	    contactNormal = Vector2::Right;
	} else {
	    contactNormal = Vector2::Left;
	}
    } else if (tNear.x < tNear.y) {
	if (rayDir.y < 0) {
	    contactNormal = Vector2::Down;
	} else {
	    contactNormal = Vector2::Up;
	}
    }

    return true;
}

bool DynamicRectsIntersect(const Rect& in, const Rect& target, Vector2& contactPoint,
			   Vector2& contactNormal, float& contactTime, float deltaTime) {
    if (in.velocity.x == 0 && in.velocity.y == 0) {
	return false;
    }

    Rect expandedTarget;
    expandedTarget.position = target.position - in.size / 2;
    expandedTarget.size = target.size + in.size;

    if (RayIntersects(in.position + in.size / 2, in.velocity, // TODO: use rigidbody velocity here.
		      expandedTarget, contactPoint, contactNormal, contactTime)) {
	if (contactTime >= 0.0f && contactTime < 1.0f) {
	    return true;
	}
    }

    return false;
}
