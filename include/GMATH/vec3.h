// gmath vec3.h
// Date: 01 01 2020
// Author: arinaivanova
// URL: https://github.com/arinaivanova/gmath
// Commentary: 3x1 Vector specialization.

#ifndef GMATH_VEC3_H_
#define GMATH_VEC3_H_

#include "vec2.h"

namespace gmath
{
	template <> struct base::Mat<3,1>
	{
		union
		{
			struct { float x, y, z; };
			struct { float u, v, w; };
			struct { float r, g, b; };
		};
		Mat()                           : x{}, y{}, z{} {}
		Mat(float X, float Y, float Z)  : x{ X }, y{ Y }, z{ Z } {}
		Mat(const Vec<3>& v)            : x{ v.x }, y{ v.y }, z{ v.z } {}

		      float& operator [] (uint i)       { assert(i < 3); return (&x)[i]; }
		const float& operator [] (uint i) const { assert(i < 3); return (&x)[i]; }

		Vec<3> operator - () const { return {-x, -y, -z}; }
		
		Vec<3> operator + (const Vec<3>& v) const { return { x + v.x, y + v.y, z + v.z }; }
		Vec<3> operator + (float val)       const { return { x + val, y + val, z + val }; }
		Vec<3> operator - (const Vec<3>& v) const { return { x - v.x, y - v.y, z - v.z }; }
		Vec<3> operator - (float val)       const { return { x - val, y - val, z - val }; }
		Vec<3> operator * (const Vec<3>& v) const { return { x * v.x, y * v.y, z * v.z }; }
		Vec<3> operator * (float val)       const { return { x * val, y * val, z * val }; }
		Vec<3> operator / (const Vec<3>& v) const
		{
			assert(v.x!=0.f&&v.y!=0.f&&v.z!=0.f);
			return { x / v.x, y / v.y, z / v.z };
		}
		Vec<3> operator / (float val) const
		{
			assert(val!=0.f); return { x / val, y / val, z / val};
		}

		Vec<3>& operator += (const Vec<3>& v) { x += v.x, y += v.y, z += v.z; return *this; }
		Vec<3>& operator += (float val)	      { x += val, y += val, z += val; return *this; }
		Vec<3>& operator -= (const Vec<3>& v) { x -= v.x, y -= v.y, z -= v.z; return *this; }
		Vec<3>& operator -= (float val)	      { x -= val, y -= val, z -= val; return *this; }
		Vec<3>& operator *= (const Vec<3>& v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
		Vec<3>& operator *= (float val)	      { x *= val, y *= val, z *= val; return *this; }
		Vec<3>& operator /= (const Vec<3>& v)
		{
			assert(v.x!=0.f&&v.y!=0.f&&v.z!=0.f);
			x /= v.x, y /= v.y, z /= v.z;
			return *this;
		}
		Vec<3>& operator /= (float val)
		{
			assert(val!=0.f);
			x /= val, y /= val, z /= val;
			return *this;
		}

		Vec<2> xy() const { return Vec2{x, y}; }
		Vec<2> uv() const { return Vec2{u, v}; }
	};
	typedef base::Vec<3> Vec3;

	inline float dot(const Vec3& lhs, const Vec3& rhs) { return rhs.x*lhs.x + rhs.y*lhs.y + rhs.z*lhs.z; }

	inline Vec3 cross(const Vec3& lhs, const Vec3& rhs)
	{
		return {(lhs.y * rhs.z - rhs.y * lhs.z),
		        (lhs.x * rhs.z - rhs.x * lhs.z),
		        (lhs.x * rhs.y - rhs.x * lhs.y)};
	}
	
	inline Vec3 normal(const Vec3& lhs, const Vec3& rhs) { return normalize(cross(lhs,rhs)); }
	
} // namespace gmath
#endif
