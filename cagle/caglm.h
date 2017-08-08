/*************************************************/
/** @CAGLM										**/
/**   ==Chung Ang university GL Mathematics		**/
/**												**/
/** @Version : v1.1								**/
/** @Author : Jeong Won Cheol					**/
/** @Contact : jwch11@gmail.com					**/
/**												**/
/** @Create : 14th May 2017						**/
/** @Last Modified: 23th May 2017				**/
/**												**/
/**	@Class : Vec3 and Mat4						**/
/*************************************************/


#pragma once

#include <cmath>

/** Auto GET and Set Function Maker */
#define AUTO_GETSET(TYPE, FUNC_NAME, PROP) \
		TYPE FUNC_NAME() const \
		{ return PROP; } \
		void FUNC_NAME(const TYPE _PROP) \
		{ PROP = _PROP; }
#define M_PI 3.14159265358979323846

namespace CAGLM {





	/*******************************************
	******* 3dim Vector ************************
	* This vector has three coordinate values
	* It can be read and write from outside.
	*******************************************/
	
	class Vec3 {
	public:
		float x, y, z;

	public:
		Vec3() {}
		Vec3(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}

		

		const float length() const								{ return sqrt(x*x + y*y + z*z); }

		/** Arithmetic operator */
		Vec3 operator-() const									{ return Vec3(-x, -y, -z); }
		Vec3 operator+(const Vec3& _v) const					{ return Vec3(x + _v.x, y + _v.y, z + _v.z); }
		Vec3& operator+=(const Vec3& _v)						{ x += _v.x; y += _v.y; z += _v.z; return *this; }
		Vec3 operator-(const Vec3& _v) const					{ return Vec3(x - _v.x, y - _v.y, z - _v.z); }
		Vec3& operator-=(const Vec3& _v)						{ x -= _v.x; y -= _v.y; z -= _v.z; return *this; }
		Vec3 operator*(const float _num) const					{ return Vec3(x*_num, y*_num, z*_num); }
		Vec3& operator*=(const Vec3& _v)						{ x *= _v.x; y *= _v.y; z *= _v.z; return *this; }
		Vec3 operator/(const float _num) const		 
		{
			if (_num == 0) throw - 1;
			else return Vec3(x / _num, y / _num, z / _num);
		}
		Vec3& operator/=(const Vec3& _v)						{ x /= _v.x; y /= _v.y; z /= _v.z; return *this; }
		
	
		/** Relational operator */
		bool operator==(const Vec3& _v) const					{ return (x == _v.x)&(y == _v.y)&(z == _v.z); }
		bool operator!=(const Vec3& _v) const					{ return !((x == _v.x)&(y == _v.y)&(z == _v.z)); }


		/** Vector operator */
		static Vec3 Normalize(const Vec3 _v)					{ return Vec3(_v.x / _v.length(), _v.y / _v.length(), _v.z / _v.length()); }
		static float Dot(const Vec3& _v1, const Vec3& _v2)		{ return _v1.x*_v2.x + _v1.y*_v2.y + _v1.z*_v2.z; }
		static Vec3 Cross(const Vec3& _v1, const Vec3& _v2)		{ return Vec3(_v1.y*_v2.z - _v1.z*_v2.y, _v1.z*_v2.x - _v1.x*_v2.z, _v1.x*_v2.y - _v1.y*_v2.x); }
		static float Angle(const Vec3& v1, const Vec3& v2)		{ return acosf(Dot(v1, v2) / (v1.length()*v2.length())); }

		/** Set */
		void operator()(const float _x, const float _y, const float _z) { x = _x; y = _y; z = _z; }

		/** GET and SET */
		AUTO_GETSET(float, X, x);
		AUTO_GETSET(float, Y, y);
		AUTO_GETSET(float, Z, z);
	};
	/*******************************************
	******* 4dim Matrix ************************
	* Matrix projected 3 dim space to 4 dim,
	* in order to support to the Homogeneous coordinate.
	*******************************************/
	class Mat4 {
	private:
		float element[4 * 4];

	public:
		Mat4()													{ setIdentity(); }

		void setIdentity(void);



		/** Matrix operator
		* GL only uses multiplication. */
		Mat4 operator* (const Mat4 _ref) const;

		/* !!!
		* This operator differs from normal that.
		* It muliplied from back to front, to aid in gl carcuration.*/
		Mat4& operator*=(const Mat4 _ref)						 { return *this = _ref * (*this); }

		
		/* !!!
		* In gl, row is counted and then column is counted, 
		* unlike a normal matrix order.*/
		/* Get and Set */
		float& operator()(const int _positionX, const int _positionY);


		


		/** Get */
		const float* getElement(void) const						 { return element; }




		/** Geometric Transformation */
		Mat4& scalef(const float _x, const float _y, const float _z);

		Mat4& translatef(const float _x, const float _y, const float _z);
		Mat4& translatev(const CAGLM::Vec3 _vec);

		Mat4& rotatef(const float _angle, const float _x, const float _y, const float _z);
		Mat4& rotatev(const float _angle, const Vec3 _v);

		Mat4& reflection(const bool _x, const bool _y, const bool _z);



		static Mat4* inverse(Mat4 _ref);
	};
}