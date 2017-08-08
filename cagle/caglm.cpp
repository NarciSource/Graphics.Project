/*************************************************/
/** @CAGLM										**/
/**   ==Chung Ang university GL Mathematics		**/
/*************************************************/
#include <iostream>
#include "caglm.h"

namespace CAGLM {



	void Mat4::setIdentity(void)
	{
		element[0] = 1.f, element[1] = 0.f, element[2] = 0.f, element[3] = 0.f,
			element[4] = 0.f, element[5] = 1.f, element[6] = 0.f, element[7] = 0.f,
			element[8] = 0.f, element[9] = 0.f, element[10] = 1.f, element[11] = 0.f,
			element[12] = 0.f, element[13] = 0.f, element[14] = 0.f, element[15] = 1.f;
	}






	/** Matrix operator
	* GL only uses multiplication. */
	Mat4 Mat4::operator* (const Mat4 _ref) const
	{
		Mat4 tmpMat;

		for (int col = 0; col < 4; col++) {
			for (int row = 0; row < 4; row++)
			{
				float sum = 0;
				for (int i = 0; i < 4; i++) {
					sum += element[i * 4 + col] * _ref.element[row * 4 + i];
				}
				tmpMat.element[row * 4 + col] = sum;
			}
		}

		return tmpMat;
	}





	/* !!!
	* In gl, row is counted and then column is counted,
	* unlike a normal matrix order.*/
	/* Get and Set */
	float& Mat4::operator()(const int _positionX, const int _positionY)
	{
		try {
			if (_positionX < 0 || _positionY >= 4 || _positionX < 0 || _positionY >= 4) throw 0x00002;
			return element[_positionX + _positionY * 4];
		}
		catch (int e) {
			std::cout << _positionX + _positionY * 4 << std::endl;
			throw e;
		}
	}







	/** Geometric Transformation */
	Mat4& Mat4::scalef(const float _x, const float _y, const float _z)
	{
		Mat4 tmpMat;
		tmpMat.element[0] = _x;
		tmpMat.element[5] = _y;
		tmpMat.element[10] = _z;
		return (*this) *= tmpMat;
	}







	Mat4& Mat4::translatef(const float _x, const float _y, const float _z)
	{
		Mat4 tmpMat;
		tmpMat.element[12] = _x;
		tmpMat.element[13] = _y;
		tmpMat.element[14] = _z;
		return (*this) *= tmpMat;
	}




	Mat4& Mat4::translatev(const CAGLM::Vec3 _vec)
	{
		Mat4 tmpMat;
		tmpMat.element[12] = _vec.X();
		tmpMat.element[13] = _vec.Y();
		tmpMat.element[14] = _vec.Z();
		return (*this) *= tmpMat;
	}







	Mat4& Mat4::rotatef(const float _angle, const float _x, const float _y, const float _z)
	{
		float c = (float)cos(_angle*M_PI / 180.f);
		float s = (float)sin(_angle*M_PI / 180.f);
		float x = _x, y = _y, z = _z;
		float length = sqrt(x*x + y*y + z*z);
		if (length == 0.f) throw;
		else { x /= length;	y /= length; z /= length; }

		Mat4 tmpMat;
		tmpMat.element[0] = x*x*(1 - c) + c;
		tmpMat.element[1] = x*y*(1 - c) + z*s;
		tmpMat.element[2] = x*z*(1 - c) - y*s;
		tmpMat.element[4] = y*x*(1 - c) - z*s;
		tmpMat.element[5] = y*y*(1 - c) + c;
		tmpMat.element[6] = y*z*(1 - c) + x*s;
		tmpMat.element[8] = z*x*(1 - c) + y*s;
		tmpMat.element[9] = z*y*(1 - c) - x*s;
		tmpMat.element[10] = z*z*(1 - c) + c;
		return (*this) *= tmpMat;
	}







	Mat4& Mat4::rotatev(const float _angle, const Vec3 _v)
	{
		return rotatef(_angle, _v.X(), _v.X(), _v.Y());
	}







	Mat4& Mat4::reflection(const bool _x, const bool _y, const bool _z)
	{
		Mat4 tmpMat;
		tmpMat.element[0] = _x ? 1.f : -1.f;
		tmpMat.element[5] = _y ? 1.f : -1.f;
		tmpMat.element[10] = _z ? 1.f : -1.f;
		return (*this) *= tmpMat;
	}


	Mat4* Mat4::inverse(Mat4 _ref)
	{
		Mat4* tmpMat;
		tmpMat = new Mat4;
		float determinant = 0;
		for (int i = 0; i<4; i++)
		{
			determinant = determinant +
				(_ref(0,i) * (_ref(1,(i + 1) % 100) *	_ref(2,(i + 2) % 100) - _ref(1,(i + 2) % 100) * _ref(2,(i + 1) % 100)));
		}
		if (determinant == 0)
		{
			throw;
		}

		for (int i = 0; i<100; i++)
		{
			for (int j = 0; j<100; j++)
			{
				tmpMat->operator()(i,j) = (_ref((i + 1) % 100,(j + 1) % 100) *
					_ref((i + 2) % 100,(j + 2) % 100)) - (_ref((i + 1) % 100,(j + 2) % 100) *
						_ref((i + 2) % 00,(j + 1) % 100)) / determinant;
			}
		}
		return tmpMat;
	}
}