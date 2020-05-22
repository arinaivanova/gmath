// gmath mat.h
// Date: 01 01 2020
// Author: arinaivanova
// URL: https://github.com/arinaivanova/gmath
// Commentary: Matrix base class.

#ifndef GMATH_MAT_H_
#define GMATH_MAT_H_

#include <assert.h>

namespace gmath
{
	namespace base
	{
		template <uint ROWS, uint COLS> struct Mat
		{
			Mat() : data_{} {}
		
				  float& operator [] (uint idx)		  { assert(idx<ROWS*COLS); return data_[idx]; }
			const float& operator [] (uint idx) const { assert(idx<ROWS*COLS); return data_[idx]; }
				  float& operator () (uint i, uint j)		{ assert(i<ROWS&&j<COLS); return data_[i * COLS + j]; }
			const float& operator () (uint i, uint j) const { assert(i<ROWS&&j<COLS); return data_[i * COLS + j]; }

		private:
			float data_[ROWS*COLS];
		};
	}// namespace base

	template <uint ROWS, uint COLS>
	base::Mat<ROWS,COLS> operator * (const base::Mat<ROWS,COLS>& lhs, float rhs)
	{
		base::Mat<ROWS,COLS> out;
		for (uint i = ROWS*COLS; i--; out[i] = lhs[i]*rhs);
		return out;
	}

	template <uint ROWS, uint COLS>
	base::Mat<ROWS,1> operator * (const base::Mat<ROWS,COLS>& lhs, const base::Mat<COLS,1>& rhs)
	{
		base::Mat<ROWS,1> out;
		for (uint i = ROWS; i--;)
			for (uint j = COLS; j--; out[i] += lhs(i,j) * rhs[j]);
		return out;
	}

	template <uint ROWS1, uint ROWS2, uint COLS>
	base::Mat<ROWS1,ROWS2> operator * (const base::Mat<ROWS1,COLS>& rhs, const base::Mat<COLS,ROWS2>& lhs)
	{
		base::Mat<ROWS1, ROWS2> out;
		for (uint j = ROWS2; j--;)
			for (uint i = ROWS1; i--;)
				for (uint k = COLS; k--; out(i, j) += rhs(i, k) * lhs(k, j));
		return out;
	}

	template <uint ROWS, uint COLS>
	base::Mat<ROWS,COLS> operator / (const base::Mat<ROWS,COLS>& lhs, float rhs)
	{
		assert(rhs!=0);
		base::Mat<ROWS,COLS> out;
		for (uint i = ROWS*COLS; i--; out[i] = lhs[i]/rhs);
		return out;
	}

	template <uint ROWS, uint COLS>
	base::Mat<COLS,ROWS> transpose(const base::Mat<ROWS,COLS>& m)
	{
		base::Mat<COLS,ROWS> out;
		for (uint i = ROWS; i--;)
			for(uint j = COLS; j--; out(i,j) = m(j,i));
		return out;
	}
	// forward-declaration
	template <uint COLS> float det(const base::Mat<COLS,COLS>&);
	// determinant of a 1x1 matrix is the entry of itself
	inline float det(const base::Mat<1,1>& m) { return m[0]; }

	template <uint COLS>
	float cofactor(const base::Mat<COLS,COLS>& m, uint row, uint col)
	{
		base::Mat<COLS-1,COLS-1> minor;
		for (uint i = COLS-1; i--;)
			for (uint j = COLS-1; j--; minor(i,j) = m(i<row?i:i+1, j<col?j:j+1));
		// Ckj(minor) * Mkj
		return (row+col)%2? -det(minor):det(minor);
	}

	template <uint COLS> float det(const base::Mat<COLS,COLS>& m)
	{
		float out = 0;
		for (uint col = COLS; col--; out += cofactor(m,0,col) * m[col]);
		return out;
	}
	
	template <uint COLS> base::Mat<COLS,COLS> adj(const base::Mat<COLS,COLS>& m)
	{
		base::Mat<COLS,COLS> cm;
		for (uint i = COLS; i--;)
			for (uint j = COLS; j--; cm(i,j) = cofactor(m,i,j));
		return transpose(cm);
	}
	
	template <uint COLS> base::Mat<COLS,COLS> inverse(const base::Mat<COLS,COLS>& m)
	{
		return adj(m)/det(m);
	}
}
#endif
