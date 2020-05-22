// gmath vec2.h
// Date: 01 01 2020
// Author: arinaivanova
// URL: https://github.com/arinaivanova/gmath
// Commentary: 2x1 Vector specialization.

#ifndef GMATH_VEC2_H_
#define GMATH_VEC2_H_

#include "vec.h"

namespace gmath
{
	template <> struct base::Mat<2,1>
	{
		union
		{
			struct { float x, y; };
			struct { float u, v; };
			struct { float s, t; };
		};
		Mat()                 : x{}, y{} {}
		Mat(float X, float Y) : x{ X }, y{ Y } {}
		Mat(const Vec<2>& v)  : x{ v.x }, y{ v.y } {}

		      float& operator [] (uint i)       { assert(i < 2); return (&x)[i]; }
		const float& operator [] (uint i) const { assert(i < 2); return (&x)[i]; }

		Vec<2> operator - () const { return {-x, -y}; }

		Vec<2> operator + (const Vec<2>& v) const { return { x + v.x, y + v.y }; }
		Vec<2> operator + (float val)       const { return { x + val, y + val }; }
		Vec<2> operator - (const Vec<2>& v) const { return { x - v.x, y - v.y }; }
		Vec<2> operator - (float val)       const { return { x - val, y - val }; }
		Vec<2> operator * (const Vec<2>& v) const { return { x * v.x, y * v.y }; }
		Vec<2> operator * (float val)       const { return { x * val, y * val }; }
		Vec<2> operator / (const Vec<2>& v) const
		{
			assert(v.x!=0.f&&v.y!=0.f);
			return { x / v.x, y / v.y};
		}
		Vec<2> operator / (float val) const
		{
			assert(val!=0.f);
			return { x / val, y / val};
		}
		
		Vec<2>& operator += (const Vec<2>& v) { x += v.x, y += v.y; return *this; }
		Vec<2>& operator += (float val)       { x += val, y += val; return *this; }
		Vec<2>& operator -= (const Vec<2>& v) { x -= v.x, y -= v.y; return *this; }
		Vec<2>& operator -= (float val)       { x -= val, y -= val; return *this; }
		Vec<2>& operator *= (const Vec<2>& v) { x *= v.x, y *= v.y; return *this; }
		Vec<2>& operator *= (float val)       { x *= val, y *= val; return *this; }
		Vec<2>& operator /= (const Vec<2>& v)
		{
			assert(v.x!=0.f&&v.y!=0.f);
			x /= v.x, y /= v.y;
			return *this;
		}
		Vec<2>& operator /= (float val)
		{
			assert(val!=0.f);
			x /= val, y /= val;
			return *this;
		}
	};
	typedef base::Vec<2> Vec2;

	inline float dot(const Vec2& lhs,const Vec2& rhs) { return rhs.x * lhs.x + rhs.y * lhs.y; }
	
	// returns determinant of the counter-clockwise triangle with vertices <v2,v0,v1>.
	// used to determine the orientation of a triangle or whether a point lies inside or outside of edge
	inline float edge(const Vec2& v0, const Vec2& v1, const Vec2& v2)
	{
		// Front-facing = det((v1-v0), (v2-v0)) < 0 ? clockwise : counter-clockwise
		return v2.x*(v0.y - v1.y) + v2.y*(v1.x - v0.x) + v0.x*v1.y - v0.y*v1.x;
	}
	
} // namespace gmath
#endif
