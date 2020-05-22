// gmath vec.h
// Date: 01 01 2020
// Author: arinaivanova
// URL: https://github.com/arinaivanova/gmath
// Commentary: Vector base class.

#ifndef GMATH_VEC_H_
#define GMATH_VEC_H_

#include <cmath>
#include "mat.h"

namespace gmath
{
	namespace base
	{
		template <uint ROWS> struct Mat<ROWS,1>
		{
			Mat() : data_{} {}
			
			      float& operator [] (uint i)       { assert(i < ROWS); return data_[i]; }
			const float& operator [] (uint i) const { assert(i < ROWS); return data_[i]; }

		private:
			float data_[ROWS];
		};

		template <uint ROWS> using Vec = Mat<ROWS, 1>;
	}// namespace base

	template <uint ROWS>
	float dot(const base::Vec<ROWS>& lhs, const base::Vec<ROWS>& rhs)
	{
		float out = 0.f;
		for (uint i = ROWS; i--; out += rhs[i]*lhs[i]);
		return out;
	}

	template <uint ROWS>
	float mag(const base::Vec<ROWS>& v) { return sqrtf(dot(v,v)); }

	template <uint ROWS>
	base::Vec<ROWS> normalize(const base::Vec<ROWS>& v)
	{
		const float m = mag(v);
		return m ? v/m : base::Vec<ROWS>{};
	}

	template <uint ROWS>
	base::Vec<ROWS> lerp(const base::Vec<ROWS>& v0, const base::Vec<ROWS>& v1, float t)
	{
		return v0*(1.f-t) + v1*t;
	}
} // namespace gmath
#endif
