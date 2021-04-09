#include "Math.h"

const Vector2 Vector2::Zero(0.0f, 0.0f);
const Vector2 Vector2::Up(0.0f, -1.0f);
const Vector2 Vector2::Down(0.0f, 1.0f);
const Vector2 Vector2::Left(-1.0f, 0.0f);
const Vector2 Vector2::Right(1.0f, 0.0f);

Rect::Rect(float x, float y, float width, float height)
    : position(Vector2(x, y)),
      size(Vector2(width, height)) {}

Rect::Rect(Vector2 position, Vector2 size)
    : position(position), size(size) {}

bool Rect::Contains(const Vector2& point) const {
    return (point.x >= position.x && point.y >= position.y &&
	    point.x < position.x + size.x && point.y < position.y + size.y);
}

bool Rect::Intersects(const Rect& rect) const {
    return (position.x < rect.position.x + rect.size.x &&
	    position.x + size.x > rect.position.x &&
	    position.y < rect.position.y + rect.size.y &&
	    position.y + size.y > rect.position.y);
}
