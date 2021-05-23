#pragma once

class Vector2;
class Rectangle;

namespace Physics {
    bool GetLineIntersectionTime(const Vector2& startA,
				 const Vector2& endA,
				 const Vector2& startB,
				 const Vector2& endB,
				 float& time);

    bool GetRayIntersectionTime(const Vector2& start,
				const Vector2& direction,
				const Rectangle& rect,
				float& time);
}
