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
	void ViewMatrix::pilotView(const CAGLM::Vec3 eyePoint, const float roll, const float yaw, const float pitch)
	{
		setIdentity();
		
		rotatef(-roll, 0, 0, 1);
		rotatef(-yaw, 0, 1, 0);
		rotatef(-pitch, 1, 0, 0);
		translatef(-eyePoint.X(), -eyePoint.Y(), -eyePoint.Z());
	}







	/** Rectangular Coordinate System = RCS
	* Use eyePoint, focus(at)Point and camera's upVector
	* to change direction camera is looking at
	* This system also represent slope at focus */
	void ViewMatrix::lookAt(const CAGLM::Vec3 eyePoint, const CAGLM::Vec3 atPoint, const CAGLM::Vec3 upVector)
	{	//eye = vrp, up = vup

		CAGLM::Vec3 n =  eyePoint - atPoint;
		CAGLM::Vec3 u = CAGLM::Vec3::Cross(n, upVector);
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

		(*this)(0, 3) = -CAGLM::Vec3::Dot(eyePoint, u);
		(*this)(1, 3) = -CAGLM::Vec3::Dot(eyePoint, v);
		(*this)(2, 3) = -CAGLM::Vec3::Dot(eyePoint, n);
	}






	/** Perspective Projection has depth to be known
	* The arguments define projection space. */
	void ProjectionMatrix::frustum(float left, float right, float bottom, float top, float near, float far)
	{
		setIdentity();
		
		(*this)(0, 0) = -(2 * near) / (right - left);
		(*this)(0, 2) = -(right + left) / (right - left);
		(*this)(1, 1) = -(2 * near) / (top - bottom);
		(*this)(1, 2) = (top + bottom) / (top - bottom);
		(*this)(2, 2) = -(far + near) / (far - near);
		(*this)(3, 2) = -1;
		(*this)(2, 3) = -2 * (far*near) / (far - near);
		(*this)(3, 3) = 0;
		
	}







	/*** This is also perspective projection
	* It is easy to understand by fovy and aspect */
	void ProjectionMatrix::perspective(float fovy, float aspect, float near, float far)
	{
		float top = -2 * near*tan(fovy / 2);
		float bottom = -top;
		float right = aspect * top;
		float left = -right;
		frustum(left, right, bottom, top, near, far);
	}







	/** Parallel Projection has not depth to be known
	* This is all taken no care of depth and is expressed in its original size */
	void ProjectionMatrix::parallel(float left, float right, float bottom, float top, float near, float far)
	{
		setIdentity();

		(*this)(0, 0) = -2 / (right - left);
		(*this)(0, 3) = -(right + left) / (right - left);
		(*this)(1, 1) = -2 / (top - bottom);
		(*this)(1, 3) = -(top + bottom) / (top - bottom);
		(*this)(2, 2) = -2 / (far - near);
		(*this)(2, 3) = -(far + near) / (far - near);
		(*this)(3, 3) = 10;
	}



}