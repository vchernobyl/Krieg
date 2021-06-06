#include "Collision.h"

AABB::AABB(const Vector2& min, const Vector2& max)
    : min(min), max(max) {}

void AABB::UpdateMinMax(const Vector2& point) {
    const auto diff = point - min;
    min += diff;
    max += diff;
}

Vector2 AABB::ClosestPointOnEdge(const Vector2& point) const {
    float minDist = Math::Fabs(point.x - min.x);
    Vector2 edgePoint = Vector2(min.x, point.y);

    if (Math::Fabs(max.x - point.x) < minDist) {
	minDist = Math::Fabs(max.x - point.x);
	edgePoint = Vector2(max.x, point.y);
    }
    if (Math::Fabs(max.y - point.y) < minDist) {
	minDist = Math::Fabs(max.y - point.y);
	edgePoint = Vector2(point.x, max.y);
    }
    if (Math::Fabs(min.y - point.y) < minDist) {
	minDist = Math::Fabs(min.y - point.y);
	edgePoint = Vector2(point.x, min.y);
    }

    return edgePoint;
}

AABB MinkowskiDifference(const AABB& a, const AABB& b) {
    const auto topLeft = a.min - b.max;
    const auto fullSize = (a.max - a.min) + (b.max - b.min);
    return AABB(topLeft, topLeft + fullSize);
}

float LineIntersectionTime(const Vector2& startA,
			   const Vector2& endA,
			   const Vector2& startB,
			   const Vector2& endB) {
    const auto r = endA - startA;
    const auto s = endB - startB;

    float numerator = Vector2::Cross(startB - startA, r);
    float denominator = Vector2::Cross(r, s);

    if (numerator == 0.0f && denominator == 0.0f) return Math::Infinity;
    if (denominator == 0.0f) return Math::Infinity;

    float u = numerator / denominator;
    float t = Vector2::Cross(startB - startA, s) / denominator;

    if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
	return t;
    }

    return Math::Infinity;
}
