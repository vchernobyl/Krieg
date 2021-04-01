#pragma once

#include "Math.h"
#include <algorithm>

namespace Collisions {    
    bool PointIntersects(const Vector2& p, const Rect& r) {
	return (p.x >= r.position.x && p.y >= r.position.y &&
		p.x < r.position.x + r.size.x && p.y < r.position.y + r.size.y);
    }

    bool RectsIntersect(const Rect& r1, const Rect& r2) {
	return (r1.position.x < r2.position.x + r2.size.x &&
		r1.position.x + r1.size.x > r2.position.x &&
		r1.position.y < r2.position.y + r2.size.y &&
		r1.position.y + r1.size.y > r2.position.y);
    }

    bool RayIntersects(const Vector2& rayOrigin, const Vector2& rayDir, const Rect& target,
		       Vector2& contactPoint, Vector2& contactNormal, float& tHitNear) {
	Vector2 tNear = (target.position - rayOrigin) / rayDir;
	Vector2 tFar = (target.position + target.size - rayOrigin) / rayDir;

	if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
	if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);

	if (tNear.x > tFar.y || tNear.y > tFar.x) return false;

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
}
