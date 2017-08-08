/*************************************************/
/** @CAGLE MVP									**/
/**   ==Chung Ang university GL Engine			**/
/**		ModelViewProjection support				**/
/*************************************************/

#include <iostream>
#include "caglemvp.h"

namespace CAGLE {

	/** Pilot View Coordinate System = PVCS
	* Use eyePoint, roll, yaw and pitch
	* to change direction camera is looking at */
	void ViewMatrix::pilotView(const CAGLM::Vec3 _eyePoint, const float _roll, const float _yaw, const float _pitch)
	{
		setIdentity();
		
		rotatef(-_roll, 0, 0, 1);
		rotatef(-_yaw, 0, 1, 0);
		rotatef(-_pitch, 1, 0, 0);
		translatef(-_eyePoint.X(), -_eyePoint.Y(), -_eyePoint.Z());
	}







	/** Rectangular Coordinate System = RCS
	* Use eyePoint, focus(at)Point and camera's upVector
	* to change direction camera is looking at
	* This system also represent slope at focus */
	void ViewMatrix::lookAt(const CAGLM::Vec3 _eyePoint, const CAGLM::Vec3 _atPoint, const CAGLM::Vec3 _upVector)
	{	//eye = vrp, up = vup

		CAGLM::Vec3 n =  _eyePoint - _atPoint;
		CAGLM::Vec3 u = CAGLM::Vec3::Cross(n, _upVector);
		CAGLM::Vec3 v = CAGLM::Vec3::Cross(u, n);

		n = CAGLM::Vec3::Normalize(n);
		u = CAGLM::Vec3::Normalize(u);
		v = CAGLM::Vec3::Normalize(v);


		setIdentity();

		(*this)(0, 0) = u.X();
		(*this)(0, 1) = u.Y();
		(*this)(0, 2) = u.Z();

		(*this)(1, 0) = v.X();
		(*this)(1, 1) = v.Y();
		(*this)(1, 2) = v.Z();

		(*this)(2, 0) = n.X();
		(*this)(2, 1) = n.Y();
		(*this)(2, 2) = n.Z();

		(*this)(0, 3) = -CAGLM::Vec3::Dot(_eyePoint, u);
		(*this)(1, 3) = -CAGLM::Vec3::Dot(_eyePoint, v);
		(*this)(2, 3) = -CAGLM::Vec3::Dot(_eyePoint, n);
	}






	/** Perspective Projection has depth to be known
	* The arguments define projection space. */
	void ProjectionMatrix::frustum(float _left, float _right, float _bottom, float _top, float _near, float _far)
	{
		setIdentity();
		
		(*this)(0, 0) = -(2 * _near) / (_right - _left);
		(*this)(0, 2) = -(_right + _left) / (_right - _left);
		(*this)(1, 1) = -(2 * _near) / (_top - _bottom);
		(*this)(1, 2) = (_top + _bottom) / (_top - _bottom);
		(*this)(2, 2) = -(_far + _near) / (_far - _near);
		(*this)(3, 2) = -1;
		(*this)(2, 3) = -2 * (_far*_near) / (_far - _near);
		(*this)(3, 3) = 0;
		
	}







	/*** This is also perspective projection
	* It is easy to understand by fovy and aspect */
	void ProjectionMatrix::perspective(float _fovy, float _aspect, float _near, float _far)
	{
		float top = -2 * _near*tan(_fovy / 2);
		float bottom = -top;
		float right = _aspect * top;
		float left = -right;
		frustum(left, right, bottom, top, _near, _far);
	}







	/** Parallel Projection has not depth to be known
	* This is all taken no care of depth and is expressed in its original size */
	void ProjectionMatrix::parallel(float _left, float _right, float _bottom, float _top, float _near, float _far)
	{
		setIdentity();

		(*this)(0, 0) = -2 / (_right - _left);
		(*this)(0, 3) = -(_right + _left) / (_right - _left);
		(*this)(1, 1) = -2 / (_top - _bottom);
		(*this)(1, 3) = -(_top + _bottom) / (_top - _bottom);
		(*this)(2, 2) = -2 / (_far - _near);
		(*this)(2, 3) = -(_far + _near) / (_far - _near);
		(*this)(3, 3) = 10;
	}



}