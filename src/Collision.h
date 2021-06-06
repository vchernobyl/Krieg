#pragma once

#include "Math.h"

struct AABB {
    AABB(const Vector2& min, const Vector2& max);

    Vector2 ClosestPointOnEdge(const Vector2& point) const;
    void UpdateMinMax(const Vector2& point);

    Vector2 min;
    Vector2 max;
};

AABB MinkowskiDifference(const AABB& a, const AABB& b);

float LineIntersectionTime(const Vector2& startA,
			   const Vector2& endA,
			   const Vector2& startB,
			   const Vector2& endB);
