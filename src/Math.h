#pragma once

#include <cmath>

namespace Math {
    const float Pi = 3.1415926535f;
    const float TwoPi = Pi * 2.0f;

    inline float ToDegrees(float radians) {
	return radians * 180.0f / Pi;
    }

    inline float Sin(float angle) {
	return sinf(angle);
    }

    inline float Cos(float angle) {
	return cosf(angle);
    }

    inline bool NearZero(float val, float epsilon = 0.001f) {
	return fabs(val) <= epsilon;
    }

    inline float Fmod(float number, float denom) {
	return fmod(number, denom);
    }

    inline float Fabs(float number) {
	return fabs(number);
    }

    inline float Lerp(float a, float b, float t) {
	if (t > 1.0f) return b;
	if (t < 0.0f) return a;
	return a + t * (b - a);
    }

    inline float Sqrt(float value) {
	return sqrtf(value);
    }
}

class Vector2 {
public:
    float x, y;
    
    explicit Vector2(float x = 0, float y = 0) : x(x), y(y) {}

    friend Vector2 operator+(const Vector2& left, const Vector2& right) {
	return Vector2(left.x + right.x, left.y+ right.y);
    }

    friend Vector2 operator-(const Vector2& left, const Vector2& right) {
	return Vector2(left.x - right.x, left.y- right.y);
    }

    friend Vector2 operator*(const Vector2& left, const Vector2& right) {
	return Vector2(left.x * right.x, left.y* right.y);
    }

    friend Vector2 operator/(const Vector2& left, const Vector2& right) {
	return Vector2(left.x / right.x, left.y/ right.y);
    }

    friend Vector2 operator*(const Vector2& left, float scalar) {
	return Vector2(left.x * scalar, left.y * scalar);
    }

    friend Vector2 operator*(float scalar, const Vector2& right) {
	return Vector2(right.x * scalar, right.y * scalar);
    }

    friend Vector2 operator/(const Vector2& left, float scalar) {
	return Vector2(left.x / scalar, left.y / scalar);
    }

    Vector2& operator*=(const Vector2& v) {
	x *= v.x;
	y *= v.y;
	return *this;
    }

    Vector2& operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
	return *this;
    }

    Vector2& operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
    }

    float LengthSq() const {
	return x * x + y * y;
    }

    float Length() const {
	return Math::Sqrt(LengthSq());
    }

    void Normalize() {
	float length = Length();
	x /= length;
	y /= length;
    }

    static const Vector2 Zero;
    static const Vector2 Up;
    static const Vector2 Down;
    static const Vector2 Left;
    static const Vector2 Right;
};

struct Rect {
    Vector2 position;
    Vector2 size;
    Vector2 velocity;

    Rect(float x, float y, float width, float height);
    Rect() {}

    bool Contains(const Vector2& p) const;
    bool Intersects(const Rect& rect) const;
};
