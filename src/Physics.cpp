#include "Physics.h"
#include "Math.h"

bool Physics::GetLineIntersectionTime(const Vector2& startA,
				      const Vector2& endA,
				      const Vector2& startB,
				      const Vector2& endB,
				      float& time) {
    Vector2 r = endA - startA;
    Vector2 s = endB - startB;

    float numerator = Vector2::Cross(startB - startA, r);
    float denominator = Vector2::Cross(r, s);

    if (numerator == 0.0f && denominator == 0.0f) return false;
    if (denominator == 0.0f) return false;

    float u = numerator / denominator;
    float t = Vector2::Cross(startB - startA, s) / denominator;

    if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
	time = t;
	return true;
    }

    return false;
}
