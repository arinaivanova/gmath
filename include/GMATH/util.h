// gmath util.h
// Date: 01 01 2020
// Author: arinaivanova
// URL: https://github.com/arinaivanova/gmath
// Commentary: Misc functions in graphics programming.

#ifndef GMATH_UTIL_H_
#define GMATH_UTIL_H_

#include "vec.h"

namespace gmath
{
	constexpr float RAD_PER_DEG { 3.14159/180 };
	constexpr float DEG_PER_RAD { 180/3.14159 };
	
	inline float rad(float deg) { return RAD_PER_DEG * deg; }
	inline float deg(float rad) { return DEG_PER_RAD * rad; }

	// linearly interpolate between two values v0 and v1 with weight t
	inline float lerp(float v0, float v1, float t) { return (1.f - t)*v0 + t*v1; }

	inline float clamp(float val, float hi) { return val>hi? hi : -hi>val? -hi : val; }
	inline float clamp(float val, float lo, float hi) { assert(lo<=hi); return val<lo ? lo : val>hi ? hi : val; }
	
} // namespace gmath
#endif
