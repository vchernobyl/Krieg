#include "Math.h"

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
            point.x <= position.x + size.x && point.y <= position.y + size.y);
}

bool Rectangle::Intersects(const Rectangle& rect) const {
    return (position.x < rect.position.x + rect.size.x &&
            position.x + size.x > rect.position.x &&
            position.y < rect.position.y + rect.size.y &&
            position.y + size.y > rect.position.y);
}

static float m4Ident[4][4] = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

const Matrix4 Matrix4::Identity(m4Ident);
