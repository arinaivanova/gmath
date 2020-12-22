// gmath transform.h
// Date: 01 01 2020
// Author: arinaivanova
// URL: https://github.com/arinaivanova/gmath
// Commentary: functions that initialize transformation matrices.

#ifndef GMATH_TRANSFORM_H_
#define GMATH_TRANSFORM_H_

#include "mat4.h"
#include "quat.h"

namespace gmath
{
	// returns full rotation matrix ABC
	inline Mat4 rotate(float a, float b, float c)
	{
		const float sinA = sinf(a),cosA = cosf(a);
		const float sinB = sinf(b),cosB = cosf(b);
		const float sinC = sinf(c),cosC = cosf(c);
		return
			{
				cosC * cosB + sinC * sinA * sinB,  -sinC * cosB + cosC * sinA * sinB, cosA * sinB,	0.f,
				sinC * cosA,						cosC * cosA,					 -sinA,			0.f,
				cosC * -sinB + sinC * sinA * cosB,	sinC * sinB + cosC * sinA * cosB, cosA * cosB,	0.f,
				0.f,								0.f,							  0.f,			1.f
			};
	}

	// returns scaling matrix xyz
	inline Mat4 scale(float x, float y, float z)
	{
		return
			{
				x, 0.f, 0.f, 0.f,
				0.f, y, 0.f, 0.f,
				0.f, 0.f, z, 0.f,
				0.f, 0.f, 0.f, 1.f
			};
	}

	// returns translation matrix xyz
	inline Mat4 translate(float x, float y, float z)
	{
		return
			{
				1.f, 0.f, 0.f, x,
				0.f, 1.f, 0.f, y,
				0.f, 0.f, 1.f, z,
				0.f, 0.f, 0.f, 1.f
			};
	}
	
	// assumes FOV is in radians. returns orthogonal projection matrix.
	inline Mat4 ortho(float f, float n, float b, float t, float l, float r)
	{
		// todo:
		return Mat4();
	}

	// assumes FOV is in radians
	// returns perspective projection matrix which remaps visible vertex coordinates to [-1, 1] after W-divide
	inline Mat4 perspective(float f, float n, float b, float t, float l, float r)
	{
		return
			{
				2*n/(r-l), 0.f,       (r+l)/(r-l),  0.f,
				0.f,       2*n/(t-b), (t+b)/(t-b),  0.f,
				0.f,       0.f,      -(f+n)/(f-n), -2*f*n/(f-n),
				0.f,       0.f,      -1.f,          0.f
			};
	}

	// returns lookat matrix with given eye, target, and up vectors. equivalent to inverse of camera transform matrix.
	inline Mat4 lookat(const Vec3& eye, const Vec3& target, const Vec3& up)
	{
		const Vec3 f = normalize(eye - target);
		const Vec3 s = normalize(cross(up, f));
		const Vec3 u = cross(s, f);
		return
			{
				s.x, s.y, s.z, -dot(eye, s),
				u.x, u.y, u.z, -dot(eye, u),
				f.x, f.y, f.z, -dot(eye, f),
				0.f, 0.f, 0.f, 1.f
			};
	}

	// returns lookat matrix with given eye vector and angles a, b, c. equivalent to inverse of camera transform matrix.
	inline Mat4 lookatEuler(const Vec3& eye, float a, float b, float c)
	{
		const float sinA = sinf(a), cosA = cosf(a);
		const float sinB = sinf(b), cosB = cosf(b);
		const float sinC = sinf(c), cosC = cosf(c);
		// columns of the full rotation matrix
		const Vec3 s { cosC*cosB + sinC*sinA*sinB,  sinC*cosA, -cosC*sinB + sinC*sinA*cosB};
		const Vec3 u {-sinC*cosB + cosC*sinA*sinB,  cosC*cosA,  sinC*sinB+cosC*sinA*cosB};
		const Vec3 f {cosA*sinB, -sinA, cosA*cosB};
		return
			{
				s.x, s.y, s.z, -dot(eye, s),
				u.x, u.y, u.z, -dot(eye, u),
				f.x, f.y, f.z, -dot(eye, f),
				0.f, 0.f, 0.f,  1.f
			};
	}

	// returns matrix transform from NDC [-1,1] to viewport coordinates
	inline Mat4 viewport(float x, float y, float w, float h, float n, float f)
	{
		const float halfW = 0.5f*w, halfH = 0.5f*h;
		return
			{
				halfW, 0.f,   0.f,        x+halfW,
				0.f,   halfH, 0.f,        y+halfH,
				0.f,   0.f,   0.5f*(f-n), 0.5f*(f+n),
				0.f,   0.f,   0.f,        1.f
			};
	}
	
	// returns a rotation quaternion about an axis N by A radians
	inline Quat rotate(float a, const Vec3& n) { return {cosf(a*0.5f), n * sinf(a*0.5f)}; }

} // namespace gmath
#endif
