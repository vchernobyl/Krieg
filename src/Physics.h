#pragma once

class Vector2;

namespace Physics {
    bool GetLineIntersectionTime(const Vector2& startA,
				 const Vector2& endA,
				 const Vector2& startB,
				 const Vector2& endB,
				 float& time);
}
