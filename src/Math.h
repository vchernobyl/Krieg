#pragma once

namespace Math {
    const float Pi = 3.1415926535f;
    inline float ToDegrees(float radians) {
	return radians * 180.0f / Pi;
    }
}

class Vector2 {
public:
    float x, y;
    
    explicit Vector2(float x = 0, float y = 0) : x(x), y(y) {}

    inline Vector2 operator+(const Vector2& v) {
	return Vector2(x + v.x, y + v.y);
    }

    inline Vector2 operator-(const Vector2& v) {
	return Vector2(x - v.x, y - v.y);
    }

    inline Vector2 operator*(const Vector2& v) {
	return Vector2(x * v.x, y * v.y);
    }

    inline Vector2 operator/(const Vector2& v) {
	return Vector2(x / v.x, y / v.y);
    }
};
