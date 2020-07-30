#pragma once
#include "Vector2.h"

namespace nc {
	const float PI = 3.141592653589793238462643383279502884197f;
	const float TAU = PI * 2;
	const float HALF_PI = PI * 0.5f;
	const float RAD_TO_DEG = 180.0f / PI;

	inline float RadiansToDegrees(float radians) {
		return radians * RAD_TO_DEG;
	}

	inline float DegreesToRadians(float degrees) {
		return degrees * PI / 180.0f;
	}

	template<typename T>
	inline T Clamp(T v, T min, T max) {
		if (v < min) v = min;
		if (v > max) v = max;
		return v;
	}

	template<>
	inline Vector2 Clamp<Vector2>(Vector2 v, Vector2 min, Vector2 max) {
		v.x = Clamp(v.x, min.x, max.x);
		v.y = Clamp(v.y, min.y, max.y);
		return v;
	}

	template<typename T>
	inline T Lerp(T a, T b, float t) {
		return a + (b - a) * t;
	}
}