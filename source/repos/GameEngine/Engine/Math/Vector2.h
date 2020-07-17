#pragma once
#include <cmath>
namespace nc
{
	struct Vector2 {
		float x, y;

		Vector2() : x{0}, y{0} {}
		Vector2(float x, float y) : x{x}, y{y} {}
		Vector2(int x, int y) : x{ static_cast<float>(x) }, y{static_cast<float>(y)}{}

		float& operator[](size_t index) { return (&x)[index]; }
		const float& operator [](size_t index) const { return (&x)[index]; }

		void Set(float x, float y) { this->x = x; this->y = y; }

		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }
		Vector2& operator += (float s) { x += s; y += s; return *this; }
		Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s; y /= s; return *this; }
		
		float Length() const;
		float LengthSqr() const;
		Vector2 Normalized() const;
		void static Normalize();
		float static Distance(const Vector2& v1, const Vector2& v2);
		Vector2 static Rotate(const Vector2& v, float radians);

		static const Vector2 left;
		static const Vector2 right;
		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 forward;
	};

	inline float Vector2::Length() const {
		return std::sqrt((x * x) + (y * y));
	}

	inline float Vector2::LengthSqr() const {
		return (x * x) + (y * y);
	}

	inline float Vector2::Distance(const Vector2& v1, const Vector2& v2) {
		Vector2 v = v1 - v2;
		return v.Length();
	}

	inline Vector2 Vector2::Rotate(const Vector2& v, float radians) {
		float x = v.x * std::cos(radians) - v.y * std::sin(radians);
		float y = v.x * std::sin(radians) + v.y * std::cos(radians);
		return { x, y };
	}
}