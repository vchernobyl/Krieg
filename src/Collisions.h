#pragma once

#include "Math.h"
#include <algorithm>

namespace Collisions {    
    bool RayIntersects(const Vector2& rayOrigin, const Vector2& rayDir, const Rect& target,
		       Vector2& contactPoint, Vector2& contactNormal, float& tHitNear) {
	Vector2 tNear = (target.position - rayOrigin) / rayDir;
	Vector2 tFar = (target.position + target.size - rayOrigin) / rayDir;

	if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
	if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);

	if (tNear.x > tFar.y || tNear.y > tFar.x) return false;

	// Replace min/max with the one from Math namespace
	tHitNear = std::max(tNear.x, tNear.y);
	float tHitFar = std::min(tFar.x, tFar.y);

	if (tHitFar < 0) return false;

	contactPoint = rayOrigin + rayDir * tHitNear;

	if (tNear.x > tNear.y) {
	    if (rayDir.x < 0) {
		contactNormal = Vector2(1, 0);
	    } else {
		contactNormal = Vector2(-1, 0);
	    }
	} else if (tNear.x < tNear.y) {
	    if (rayDir.y < 0) {
		contactNormal = Vector2(0, 1);
	    } else {
		contactNormal = Vector2(0, -1);
	    }
	}

	return true;
    }

    bool DynamicRectsIntersect(const Rect& src, const Rect& target, Vector2& contactPoint,
			       Vector2& contactNormal, float& contactTime, float deltaTime) {
	if (src.velocity.x == 0 && src.velocity.y == 0) {
	    return false;
	}

	Rect expandedTarget;
	expandedTarget.position = target.position - src.size / 2;
	expandedTarget.size = target.size + src.size;

	if (RayIntersects(src.position + src.size / 2, src.velocity * deltaTime,
			  expandedTarget, contactPoint, contactNormal, contactTime)) {
	    if (contactTime <= 1.0f) {
		return true;
	    }
	}

	return false;
    }
}
