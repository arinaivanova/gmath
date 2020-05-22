// gmath mat4.h
// Date: 01 01 2020
// Author: arinaivanova
// URL: https://github.com/arinaivanova/gmath
// Commentary: 4x4 Matrix specialization.

#ifndef GMATH_MAT4_H_
#define GMATH_MAT4_H_

#include "mat.h"
#include "vec4.h"

namespace gmath
{
	template <> struct base::Mat<4, 4>
	{
		Mat() : data_{} {}
		Mat(float A00, float A01, float A02, float A03,
			float A10, float A11, float A12, float A13,
			float A20, float A21, float A22, float A23,
			float A30, float A31, float A32, float A33) : data_{}
		{
			data_[0] = A00; data_[1] = A01; data_[2] = A02; data_[3] = A03;
			data_[4] = A10; data_[5] = A11; data_[6] = A12; data_[7] = A13;
			data_[8] = A20; data_[9] = A21; data_[10] = A22;data_[11] = A23;
			data_[12] = A30;data_[13] = A31;data_[14] = A32;data_[15] = A33;
		}
			  float& operator [] (uint idx)		  { assert(idx<16); return data_[idx]; }
		const float& operator [] (uint idx) const { assert(idx<16); return data_[idx]; }
			  float& operator () (uint i, uint j)		{ assert(i<4&&j<4); return data_[i * 4 + j]; }
		const float& operator () (uint i, uint j) const { assert(i<4&&j<4); return data_[i * 4 + j]; }

		Vec4 operator * (const Vec4& v) const
		{
			return
				{
					data_[0] * v.x + data_[1] * v.y + data_[2] * v.z + data_[3] * v.w,
					data_[4] * v.x + data_[5] * v.y + data_[6] * v.z + data_[7] * v.w,
					data_[8] * v.x + data_[9] * v.y + data_[10]* v.z + data_[11]* v.w,
					data_[12]* v.x + data_[13]* v.y + data_[14]* v.z + data_[15]* v.w
				};
		}
		Vec3 operator * (const Vec3& v) const
		{
			return
				{
					data_[0] * v.x + data_[1] * v.y + data_[2] * v.z,
					data_[4] * v.x + data_[5] * v.y + data_[6] * v.z,
					data_[8] * v.x + data_[9] * v.y + data_[10]* v.z,
				};
		}
		Mat<4, 4> operator * (const Mat<4, 4>& m) const
		{
			return
				{	// ROW 0
					data_[0] * m[0] + data_[1] * m[4] + data_[2] * m[8] + data_[3] * m[12],
					data_[0] * m[1] + data_[1] * m[5] + data_[2] * m[9] + data_[3] * m[13],
					data_[0] * m[2] + data_[1] * m[6] + data_[2] * m[10]+ data_[3] * m[14],
					data_[0] * m[3] + data_[1] * m[7] + data_[2] * m[11]+ data_[3] * m[15],
					// ROW 1
					data_[4] * m[0] + data_[5] * m[4] + data_[6] * m[8] + data_[7] * m[12],
					data_[4] * m[1] + data_[5] * m[5] + data_[6] * m[9] + data_[7] * m[13],
					data_[4] * m[2] + data_[5] * m[6] + data_[6] * m[10]+ data_[7] * m[14],
					data_[4] * m[3] + data_[5] * m[7] + data_[6] * m[11]+ data_[7] * m[15],
					// ROW 2
					data_[8] * m[0] + data_[9] * m[4] + data_[10] * m[8] + data_[11] * m[12],
					data_[8] * m[1] + data_[9] * m[5] + data_[10] * m[9] + data_[11] * m[13],
					data_[8] * m[2] + data_[9] * m[6] + data_[10] * m[10]+ data_[11] * m[14],
					data_[8] * m[3] + data_[9] * m[7] + data_[10] * m[11]+ data_[11] * m[15],
					// ROW 3
					data_[12] * m[0] + data_[13] * m[4] + data_[14] * m[8] + data_[15] * m[12],
					data_[12] * m[1] + data_[13] * m[5] + data_[14] * m[9] + data_[15] * m[13],
					data_[12] * m[2] + data_[13] * m[6] + data_[14] * m[10]+ data_[15] * m[14],
					data_[12] * m[3] + data_[13] * m[7] + data_[14] * m[11]+ data_[15] * m[15]
				};
		}
	private:
		float data_[16];
	};
	typedef base::Mat<4, 4> Mat4;

	inline Mat4 transpose(const Mat4& m)
	{
		return
			{
				m[0],m[4],m[8], m[12],
				m[1],m[5],m[9], m[13],
				m[2],m[6],m[10],m[14],
				m[3],m[7],m[11],m[15]
			};
	}

	inline Mat4 inverse(const Mat4& m)
	{
		const float A1015 = m[10]*m[15]-m[11]*m[14];
		const float A0915 = m[9]*m[15]-m[11]*m[13];
		const float A0914 = m[9]*m[14]-m[10]*m[13];
		const float A0815 = m[8]*m[15]-m[11]*m[12];
		const float A0814 = m[8]*m[14]-m[10]*m[12];
		const float A0813 = m[8]*m[13]-m[9]*m[12];
		const float A0615 = m[6]*m[15]-m[7]*m[14];
		const float A0515 = m[5]*m[15]-m[7]*m[13];
		const float A0514 = m[5]*m[14]-m[6]*m[13];
		const float A0415 = m[4]*m[15]-m[7]*m[12];
		const float A0414 = m[4]*m[14]-m[6]*m[12];
		const float A0413 = m[4]*m[13]-m[5]*m[12];
		const float A0611 = m[6]*m[11]-m[7]*m[10];
		const float A0511 = m[5]*m[11]-m[7]*m[9];
		const float A0510 = m[5]*m[10]-m[6]*m[9];
		const float A0411 = m[4]*m[11]-m[7]*m[8];
		const float A0410 = m[4]*m[10]-m[6]*m[8];
		const float A0409 = m[4]*m[9]-m[5]*m[8];
		const float dt = 1.f / (m[0]*(m[5]*A1015 - m[6]*A0915 + m[7]*A0914)
								-m[1]*(m[4]*A1015 - m[6]*A0815 + m[7]*A0814)
								+m[2]*(m[4]*A0915 - m[5]*A0815 + m[7]*A0813)
								-m[3]*(m[4]*A0914 - m[5]*A0814 + m[6]*A0813));
		return
			{   // ROW 0
				dt * (m[5]*A1015 - m[6]*A0915 + m[7]*A0914),
				dt * -(m[1]*A1015 - m[2]*A0915 + m[3]*A0914),
				dt * (m[1]*A0615 - m[2]*A0515 + m[3]*A0514),
				dt * -(m[1]*A0611 - m[2]*A0511 + m[3]*A0510),
				// ROW 1
				dt * -(m[4]*A1015 - m[6]*A0815 + m[7]*A0814),
				dt * (m[0]*A1015 - m[2]*A0815 + m[3]*A0814),
				dt * -(m[0]*A0615 - m[2]*A0415 + m[3]*A0414),
				dt * (m[0]*A0611 - m[2]*A0411 + m[3]*A0410),
				// ROW 2
				dt * (m[4]*A0915 - m[5]*A0815 + m[7]*A0813),
				dt * -(m[0]*A0915 - m[1]*A0815 + m[3]*A0813),
				dt * (m[0]*A0515 - m[1]*A0415 + m[3]*A0413),
				dt * -(m[0]*A0511 - m[1]*A0411 + m[3]*A0409),
				// ROW 3
				dt * -(m[4]*A0914 - m[5]*A0814 + m[6]*A0813),
				dt * (m[0]*A0914 - m[1]*A0814 + m[2]*A0813),
				dt * -(m[0]*A0514 - m[1]*A0414 + m[2]*A0413),
				dt * (m[0]*A0510 - m[1]*A0410 + m[2]*A0409)
			};
	}
} // namespace gmath
#endif
