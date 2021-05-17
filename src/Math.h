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

    template <typename T>
    inline int Sign(T value) {
	return (value > 0) ? 1 : (value < 0) ? -1 : 0;
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

    friend bool operator==(const Vector2& left, const Vector2& right) {
	return left.x == right.x && left.y == right.y;
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

    static float Dot(const Vector2& a, const Vector2& b) {
	return a.x * b.x + a.y * b.y;
    }

    static Vector2 Reflect(const Vector2& v, const Vector2& n) {
	return v - 2.0f * Vector2::Dot(v, n) * n;
    }

    static Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {
	return Vector2(a + t * (b - a));
    }

    static const Vector2 Zero;
    static const Vector2 One;
    static const Vector2 Up;
    static const Vector2 Down;
    static const Vector2 Left;
    static const Vector2 Right;
};

class Vector3 {
public:
    float x, y, z;

    explicit Vector3(float x = 0, float y = 0, float z = 0)
	: x(x), y(y), z(z) {}

    friend Vector3 operator+(const Vector3& a, const Vector3& b) {
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    friend Vector3 operator-(const Vector3& a, const Vector3& b) {
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    friend Vector3 operator*(const Vector3& v, float scalar) {
	return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
    }

    friend Vector3 operator*(float scalar, const Vector3& v) {
	return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
    }

    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t) {
	return Vector3(a + t * (b - a));
    }
};

class Vector4 {
public:
    float x, y, z, w;

    explicit Vector4(float x = 0, float y = 0, float z = 0, float w = 0)
	: x(x), y(y), z(z), w(w) {}

    friend Vector4 operator+(const Vector4& a, const Vector4& b) {
	return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }

    friend Vector4 operator-(const Vector4& a, const Vector4& b) {
	return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }

    friend Vector4 operator*(const Vector4& v, float scalar) {
	return Vector4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
    }

    friend Vector4 operator*(float scalar, const Vector4& v) {
	return Vector4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
    }

    static Vector4 Lerp(const Vector4& a, const Vector4& b, float t) {
	return Vector4(a + t * (b - a));
    }
};

class Rectangle {
public:
    Vector2 position;
    Vector2 size;
    
    explicit Rectangle(float x = 0, float y = 0, float width = 0, float height = 0);
    explicit Rectangle(Vector2 position, Vector2 size);

    bool Contains(const Vector2& point) const;
    bool Intersects(const Rectangle& rect) const;
};
