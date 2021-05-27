#include "Math.h"
#include <SDL.h>
#include <cassert>

const Vector2 Vector2::Zero(0.0f, 0.0f);
const Vector2 Vector2::One(1.0f, 1.0f);
const Vector2 Vector2::Up(0.0f, -1.0f);
const Vector2 Vector2::Down(0.0f, 1.0f);
const Vector2 Vector2::Left(-1.0f, 0.0f);
const Vector2 Vector2::Right(1.0f, 0.0f);

Rectangle::Rectangle(float x, float y, float width, float height)
    : position(Vector2(x, y)),
      size(Vector2(width, height)) {}

Rectangle::Rectangle(Vector2 position, Vector2 size)
    : position(position), size(size) {}

bool Rectangle::Contains(const Vector2& point) const {
    return (point.x >= position.x && point.y >= position.y &&
	    point.x < position.x + size.x && point.y < position.y + size.y);
}

bool Rectangle::Intersects(const Rectangle& rect) const {
    return (position.x < rect.position.x + rect.size.x &&
	    position.x + size.x > rect.position.x &&
	    position.y < rect.position.y + rect.size.y &&
	    position.y + size.y > rect.position.y);
}

float Rectangle::RayIntersectionTime(const Vector2& start, const Vector2& direction, Vector2& normal) {
    auto end = start + direction;
    auto max = position + size;
    auto min = position;

    float minTime = LineIntersectionTime(start, end, Vector2(min.x, min.y), Vector2(min.x, max.y));
    normal = Vector2(-1, 0);
    float time;

    time = LineIntersectionTime(start, end, Vector2(min.x, max.y), Vector2(max.x, max.y));
    if (time < minTime)	{
	normal = Vector2(0, 1);
	minTime = time;
    }

    time = LineIntersectionTime(start, end, Vector2(max.x, max.y), Vector2(max.x, min.y));
    if (time < minTime) {
	normal = Vector2(1, 0);
	minTime = time;
    }

    time = LineIntersectionTime(start, end, Vector2(max.x, min.y), Vector2(min.x, min.y));
    if (time < minTime)	{
	normal = Vector2(0, -1);
	minTime = time;
    }

    return minTime;
}

Rectangle MinkowskiDifference(const Rectangle& a, const Rectangle& b) {
    auto topLeft = b.position - (a.position + a.size);
    auto fullSize = a.size + b.size;
    return Rectangle(topLeft, fullSize);
}

float LineIntersectionTime(const Vector2& startA,
			   const Vector2& endA,
			   const Vector2& startB,
			   const Vector2& endB) {
    auto r = endA - startA;
    auto s = endB - startB;

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
