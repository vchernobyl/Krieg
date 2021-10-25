#pragma once

#include <cmath>
#include <limits>
#include <algorithm>

namespace Math {
    const float Pi = 3.1415926535f;
    const float TwoPi = Pi * 2.0f;
    const float Infinity = std::numeric_limits<float>::infinity();

    inline float ToDegrees(float radians) {
	return radians * 180.0f / Pi;
    }

    inline float Sin(float angle) {
	return sinf(angle);
    }

    inline float Cos(float angle) {
	return cosf(angle);
    }

    inline float Acos(float angle) {
	return acos(angle);
    }

    inline float Atan2(float y, float x) {
	return atan2(y, x);
    }

    inline bool NearZero(float val, float epsilon = 0.001f) {
	return fabs(val) <= epsilon;
    }

    inline float Mod(float number, float denom) {
	return fmod(number, denom);
    }

    inline float Abs(float number) {
	return fabs(number);
    }

    inline float Floor(float number) {
	return floor(number);
    }

    inline float Round(float number) {
	return round(number);
    }

    inline float Clamp(float number, float low, float high) {
	return std::clamp(number, low, high);
    }

    inline float Max(float a, float b) {
	return (a > b) ? a : b;
    }

    inline float Min(float a, float b) {
	return (a < b) ? a : b;
    }

    inline float Lerp(float a, float b, float t) {
	if (t > 1.0f) return b;
	if (t < 0.0f) return a;
	return a + t * (b - a);
    }

    inline float Sqrt(float value) {
	return sqrtf(value);
    }

    inline float Sign(float value) {
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

    friend Vector2 operator-(const Vector2& v) {
	return Vector2(-v.x, -v.y);
    }

    friend bool operator==(const Vector2& left, const Vector2& right) {
	return left.x == right.x && left.y == right.y;
    }

    friend bool operator!=(const Vector2& left, const Vector2& right) {
	return left.x != right.x || left.y != right.y;
    }

    Vector2& operator*=(const Vector2& v) {
	x *= v.x;
	y *= v.y;
	return *this;
    }

    Vector2& operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
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

    Vector2& Normalized() {
	Normalize();
	return *this;
    }

    static Vector2 Normalize(const Vector2& v) {
	float length = v.Length();
	if (length != 0.0f) {
	    return Vector2(v.x / length, v.y / length);
	}
	return Vector2::Zero;
    }

    static float Dot(const Vector2& a, const Vector2& b) {
	return a.x * b.x + a.y * b.y;
    }

    static float Cross(const Vector2& a, const Vector2& b) {
	return a.x * b.y - a.y * b.x;
    }

    static float Distance(const Vector2& a, const Vector2& b) {
	return (b - a).LengthSq();
    }

    static Vector2 Reflect(const Vector2& v, const Vector2& n) {
	return v - 2.0f * Vector2::Dot(v, n) * n;
    }

    static Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {
	if (t < 0.0f) return a;
	if (t > 1.0f) return b;
	return Vector2(a + t * (b - a));
    }

    static Vector2 RotatePoint(const Vector2& point, float angle) {
	Vector2 rotated;
	rotated.x = point.x * Math::Cos(angle) - point.y * Math::Sin(angle);
	rotated.y = point.x * Math::Sin(angle) + point.y * Math::Cos(angle);
	return rotated;
    }

    // TODO: Can we instantiate them here directly?
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

    Vector3& operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
    }

    Vector3& operator+=(const Vector3& right) {
	x += right.x;
	y += right.y;
	z += right.z;
	return *this;
    }

    Vector3& operator-=(const Vector3& right) {
	x -= right.x;
	y -= right.y;
	z -= right.z;
	return *this;
    }

    float LengthSq() const {
	return (x*x + y*y + z*z);
    }

    float Length() const {
	return Math::Sqrt(LengthSq());
    }

    void Normalize() {
	float length = Length();
	x /= length;
	y /= length;
	z /= length;
    }

    static Vector3 Normalize(const Vector3& vec) {
	Vector3 temp = vec;
	temp.Normalize();
	return temp;
    }

    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t) {
	if (t < 0.0f) return a;
	if (t > 1.0f) return b;
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
	if (t < 0.0f) return a;
	if (t > 1.0f) return b;
	return Vector4(a + t * (b - a));
    }
};

// TODO: Remove this shit, use vec4 instead.
class Rectangle {
public:
    Vector2 position;
    Vector2 size;
    
    explicit Rectangle(float x = 0, float y = 0, float width = 0, float height = 0);
    explicit Rectangle(Vector2 position, Vector2 size);
    
    bool Contains(const Vector2& point) const;
    bool Intersects(const Rectangle& rect) const;
};

class Matrix4 {
public:
    float mat[4][4];

    Matrix4() { *this = Matrix4::Identity; }

    explicit Matrix4(float inMat[4][4]) { memcpy(mat, inMat, 16 * sizeof(float)); }

    const float* GetAsFloatPtr() const {
	return reinterpret_cast<const float*>(&mat[0][0]);
    }

    friend Matrix4 operator*(const Matrix4& a, const Matrix4& b) {
	Matrix4 retVal;
	// row 0
	retVal.mat[0][0] = 
	    a.mat[0][0] * b.mat[0][0] + 
	    a.mat[0][1] * b.mat[1][0] + 
	    a.mat[0][2] * b.mat[2][0] +
	    a.mat[0][3] * b.mat[3][0];

	retVal.mat[0][1] = 
	    a.mat[0][0] * b.mat[0][1] + 
	    a.mat[0][1] * b.mat[1][1] + 
	    a.mat[0][2] * b.mat[2][1] + 
	    a.mat[0][3] * b.mat[3][1];

	retVal.mat[0][2] = 
	    a.mat[0][0] * b.mat[0][2] + 
	    a.mat[0][1] * b.mat[1][2] + 
	    a.mat[0][2] * b.mat[2][2] + 
	    a.mat[0][3] * b.mat[3][2];
		
	retVal.mat[0][3] = 
	    a.mat[0][0] * b.mat[0][3] + 
	    a.mat[0][1] * b.mat[1][3] + 
	    a.mat[0][2] * b.mat[2][3] + 
	    a.mat[0][3] * b.mat[3][3];

	// row 1
	retVal.mat[1][0] = 
	    a.mat[1][0] * b.mat[0][0] + 
	    a.mat[1][1] * b.mat[1][0] + 
	    a.mat[1][2] * b.mat[2][0] + 
	    a.mat[1][3] * b.mat[3][0];

	retVal.mat[1][1] = 
	    a.mat[1][0] * b.mat[0][1] + 
	    a.mat[1][1] * b.mat[1][1] + 
	    a.mat[1][2] * b.mat[2][1] + 
	    a.mat[1][3] * b.mat[3][1];

	retVal.mat[1][2] = 
	    a.mat[1][0] * b.mat[0][2] + 
	    a.mat[1][1] * b.mat[1][2] + 
	    a.mat[1][2] * b.mat[2][2] + 
	    a.mat[1][3] * b.mat[3][2];

	retVal.mat[1][3] = 
	    a.mat[1][0] * b.mat[0][3] +
	    a.mat[1][1] * b.mat[1][3] +
	    a.mat[1][2] * b.mat[2][3] +
	    a.mat[1][3] * b.mat[3][3];

	// row 2
	retVal.mat[2][0] = 
	    a.mat[2][0] * b.mat[0][0] +
	    a.mat[2][1] * b.mat[1][0] +
	    a.mat[2][2] * b.mat[2][0] +
	    a.mat[2][3] * b.mat[3][0];

	retVal.mat[2][1] = 
	    a.mat[2][0] * b.mat[0][1] + 
	    a.mat[2][1] * b.mat[1][1] + 
	    a.mat[2][2] * b.mat[2][1] + 
	    a.mat[2][3] * b.mat[3][1];

	retVal.mat[2][2] = 
	    a.mat[2][0] * b.mat[0][2] +
	    a.mat[2][1] * b.mat[1][2] + 
	    a.mat[2][2] * b.mat[2][2] + 
	    a.mat[2][3] * b.mat[3][2];

	retVal.mat[2][3] = 
	    a.mat[2][0] * b.mat[0][3] + 
	    a.mat[2][1] * b.mat[1][3] + 
	    a.mat[2][2] * b.mat[2][3] + 
	    a.mat[2][3] * b.mat[3][3];

	// row 3
	retVal.mat[3][0] = 
	    a.mat[3][0] * b.mat[0][0] + 
	    a.mat[3][1] * b.mat[1][0] + 
	    a.mat[3][2] * b.mat[2][0] + 
	    a.mat[3][3] * b.mat[3][0];

	retVal.mat[3][1] = 
	    a.mat[3][0] * b.mat[0][1] + 
	    a.mat[3][1] * b.mat[1][1] + 
	    a.mat[3][2] * b.mat[2][1] + 
	    a.mat[3][3] * b.mat[3][1];

	retVal.mat[3][2] = 
	    a.mat[3][0] * b.mat[0][2] +
	    a.mat[3][1] * b.mat[1][2] +
	    a.mat[3][2] * b.mat[2][2] +
	    a.mat[3][3] * b.mat[3][2];

	retVal.mat[3][3] = 
	    a.mat[3][0] * b.mat[0][3] +
	    a.mat[3][1] * b.mat[1][3] +
	    a.mat[3][2] * b.mat[2][3] +
	    a.mat[3][3] * b.mat[3][3];
		
	return retVal;
    }

    Matrix4 operator*=(const Matrix4& right)  {
	*this = *this * right;
	return *this;
    }

    Vector3 GetTranslation() const {
	return Vector3(mat[3][0], mat[3][1], mat[3][2]);
    }

    Vector3 GetXAxis() const {
	return Vector3::Normalize(Vector3(mat[0][0], mat[0][1], mat[0][2]));
    }

    Vector3 GetYAxis() const {
	return Vector3::Normalize(Vector3(mat[1][0], mat[1][1], mat[1][2]));
    }

    Vector3 GetZAxis() const {
	return Vector3::Normalize(Vector3(mat[2][0], mat[2][1], mat[2][2]));
    }

    Vector3 GetScale() const {
	Vector3 scale;
	scale.x = Vector3(mat[0][0], mat[0][1], mat[0][2]).Length();
	scale.y = Vector3(mat[1][0], mat[1][1], mat[1][2]).Length();
	scale.z = Vector3(mat[2][0], mat[2][1], mat[2][2]).Length();
	return scale;
    }

    static Matrix4 CreateScale(float xScale, float yScale, float zScale) {
	float scale[4][4] = {
	    { xScale, 0.0f, 0.0f, 0.0f },
	    { 0.0f, yScale, 0.0f, 0.0f },
	    { 0.0f, 0.0f, zScale, 0.0f },
	    { 0.0f, 0.0f, 0.0f, 1.0f },
	};
	return Matrix4(scale);
    }

    static Matrix4 CreateScale(const Vector3& scale) {
	return CreateScale(scale.x, scale.y, scale.y);
    }

    static Matrix4 CreateScale(float scale) {
	return CreateScale(scale, scale, scale);
    }

    static Matrix4 CreateRotationX(float theta) {
	float rotation[4][4] = {
	    { 1.0f, 0.0f, 0.0f, 0.0f },
	    { 0.0f, Math::Cos(theta), Math::Sin(theta), 0.0f },
	    { 0.0f, -Math::Sin(theta), Math::Cos(theta), 0.0f },
	    { 0.0f, 0.0f, 0.0f, 1.0f }
	};
	return Matrix4(rotation);
    }

    static Matrix4 CreateRotationY(float theta) {
	float rotation[4][4] = {
	    { Math::Cos(theta), 0.0f, -Math::Sin(theta), 0.0f },
	    { 0.0f, 1.0f, 0.0f, 0.0f },
	    { Math::Sin(theta), 0.0f, Math::Cos(theta), 0.0f },
	    { 0.0f, 0.0f, 0.0f, 1.0f }
	};
	return Matrix4(rotation);
    }

    static Matrix4 CreateRotationZ(float theta) {
	float rotation[4][4] = {
	    { Math::Cos(theta), Math::Sin(theta), 0.0f, 0.0f },
	    { -Math::Sin(theta), Math::Cos(theta), 0.0f, 0.0f },
	    { 0.0f, 0.0f, 1.0f, 0.0f },
	    { 0.0f, 0.0f, 0.0f, 1.0f }
	};
	return Matrix4(rotation);
    }

    static Matrix4 CreateTranslation(const Vector3& t) {
	float translation[4][4] = {
	    { 1.0f, 0.0f, 0.0f, 0.0f },
	    { 0.0f, 1.0f, 0.0f, 0.0f },
	    { 0.0f, 0.0f, 1.0f, 0.0f },
	    { t.x, t.y, t.z, 1.0f }
	};
	return Matrix4(translation);
    }

    static Matrix4 CreateSimpleViewProjection(float width, float height) {
	float projection[4][4] = {
	    { 2.0f/width, 0.0f, 0.0f, 0.0f },
	    { 0.0f, 2.0f/height, 0.0f, 0.0f },
	    { 0.0f, 0.0f, 1.0f, 0.0f },
	    { 0.0f, 0.0f, 1.0f, 1.0f }
	};
	return Matrix4(projection);
    }

    static Matrix4 CreateOrtho(float width, float height, float near, float far) {
	float ortho[4][4] = {
	    { 2.0f / width, 0.0f, 0.0f, 0.0f },
	    { 0.0f, 2.0f / height, 0.0f, 0.0f },
	    { 0.0f, 0.0f, 1.0f / (far - near), 0.0f },
	    { 0.0f, 0.0f, near / (near - far), 1.0f }
	};
	return Matrix4(ortho);
    }
    
    static const Matrix4 Identity;
};

namespace Color {
    static const Vector4 Red(1.0f, 0.0f, 0.0f, 1.0f);
    static const Vector4 Green(0.0f, 1.0f, 0.0f, 1.0f);
    static const Vector4 Blue(0.0f, 0.0f, 1.0f, 1.0f);
    static const Vector4 White(1.0f, 1.0f, 1.0f, 1.0f);
};
