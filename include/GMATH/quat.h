// gmath quat.h
// Date: 01 01 2020
// Author: arinaivanova
// URL: https://github.com/arinaivanova/gmath
// Commentary: Quaternion class

#ifndef GMATH_QUAT_H_
#define GMATH_QUAT_H_

#include "vec3.h"

namespace gmath
{
	struct Quat
	{
		struct { float w, x, y, z; };

		Quat() : w{}, x{}, y{}, z{} {}
		Quat(float W, float X, float Y, float Z) : w{W}, x{X}, y{Y}, z{Z} {}
		Quat(float W, const Vec3& v)             : w{W}, x{v.x}, y{v.y}, z{v.z} {}

		      float& operator [] (uint i)       { assert(i < 4); return (&w)[i]; }
		const float& operator [] (uint i) const { assert(i < 4); return (&w)[i]; }

		Quat operator + (const Quat& q) const { return {w+q.w, x+q.x, y+q.y, z+q.z}; }
   		Quat operator + (float val)     const { return {w+val, x+val, y+val, z+val}; }
		Quat operator - (const Quat& q) const { return {w-q.w, x-q.x, y-q.y, z-q.z}; }
		Quat operator - (float val)     const { return {w-val, x-val, y-val, z-val}; }
		
		Quat operator * (const Vec3& v) const
		{
			return
				{
					-x*v.x - y*v.y - z*v.z,
					w*v.x - z*v.y + y*v.z,
					z*v.x + w*v.y - x*v.z,
					x*v.y + w*v.z - y*v.x
				};
		}
		
		Quat operator * (const Quat& q) const
		{
			return
				{
					w*q.w - x*q.x - y*q.y - z*q.z,
					x*q.w + w*q.x - z*q.y + y*q.z,
					y*q.w + z*q.x + w*q.y - x*q.z,
					z*q.w - y*q.x + x*q.y + w*q.z
				};
		}
	};
}
#endif
