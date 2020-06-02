// gmath vec4.h
// Date: 01 01 2020
// Author: arinaivanova
// URL: https://github.com/arinaivanova/gmath
// Commentary: 3x1 Vector specialization.

#ifndef GMATH_VEC4_H_
#define GMATH_VEC4_H_

#include "vec3.h"

namespace gmath
{
	template <> struct base::Mat<4,1>
	{
		union
		{
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
		};
		Mat()                                   : x{}, y{}, z{}, w{} {}
		Mat(float X, float Y, float Z, float W) : x{ X }, y{ Y }, z{ Z }, w{ W } {}
		Mat(const Vec<4>& v)                    : x{ v.x }, y{ v.y }, z{ v.z }, w{ v.w } {}

		      float& operator [] (uint i)       { assert(i < 4); return (&x)[i]; }
		const float& operator [] (uint i) const { assert(i < 4); return (&x)[i]; }

		Vec<4> operator - () const { return {-x, -y, -z, -w}; }
		
		Vec<4> operator + (const Vec<4>& v) const { return {x + v.x, y + v.y, z + v.z, w + v.w}; }
		Vec<4> operator + (float val)       const { return {x + val, y + val, z + val, w + val}; }
		Vec<4> operator - (const Vec<4>& v) const { return {x - v.x, y - v.y, z - v.z, w - v.w}; }
		Vec<4> operator - (float val)       const { return {x - val, y - val, z - val, w - val}; }
		Vec<4> operator * (const Vec<4>& v) const { return {x * v.x, y * v.y, z * v.z, w * v.w}; }
		Vec<4> operator * (float val)       const { return {x * val, y * val, z * val, w * val}; }
		Vec<4> operator / (const Vec<4>& v) const
		{
			assert(v.x!=0.f&&v.y!=0.f&&v.z!=0.f&&v.w!=0.f);
			return {x / v.x, y / v.y, z / v.z, w / v.w};
		}
		Vec<4> operator / (float val) const
		{
			assert(val!=0.f);
			return {x / val, y / val, z / val, w / val};
		}

		Vec<4>& operator += (const Vec<4>& v) { x += v.x, y += v.y, z += v.z, w += v.w; return *this; };
		Vec<4>& operator += (float val)       { x += val, y += val, z += val, w += val; return *this; };
		Vec<4>& operator -= (const Vec<4>& v) { x -= v.x, y -= v.y, z -= v.z, w -= v.w; return *this; };
		Vec<4>& operator -= (float val)       { x -= val, y -= val, z -= val, w -= val; return *this; };
		Vec<4>& operator *= (const Vec<4>& v) { x *= v.x, y *= v.y, z *= v.z, w *= v.w; return *this; };
		Vec<4>& operator *= (float val)       { x *= val, y *= val, z *= val, w *= val; return *this; };
		Vec<4>& operator /= (const Vec<4>& v)
		{
			assert(v.x!=0.f&&v.y!=0.f&&v.z!=0.f&&v.w!=0.f);
			x /= v.x, y /= v.y, z /= v.z, w /= v.w;
			return *this;
		}
		void operator /= (float val)
		{
			assert(val!=0.f);
			x /= val, y /= val, z /= val, w /= val;
		}

		Vec<3> xyz() const { return Vec3{x, y, z}; } // TODO:
		Vec<3> rgb() const { return Vec3{r, g, b}; }
		Vec<2> xy() const { return Vec2{x, y}; }
	};
	typedef base::Vec<4> Vec4;

	inline float dot(const Vec4& lhs,const Vec4& rhs)
	{
		return rhs.x*lhs.x + rhs.y*lhs.y + rhs.z*lhs.z + rhs.w*lhs.w;
	}
	
	// returns line-plane intersection with given point on plane p, normal to plane n, origin of line q, and direction of line v
	inline Vec4 poiLinePlane(const Vec4& p, const Vec4& n, const Vec4& q, const Vec4& v)
	{
		return q + v*dot(p-q, n) / dot(v, n);
	}
} // namespace gmath
#endif
