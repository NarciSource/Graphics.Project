#include "camera.h"

namespace CAGLE {
	Camera::Camera() : size(1), cameraUp(CAGLM::Vec3<float>(0, 1, 0)),
		roll(0), yaw(0), pitch(0), fovy(1),
		aspect(2.0), neear(0.1f), faar(100.f),
		projectionType(PROJECTION_PERSPECTIVE), flushMap(false)
	{
		weapon.hisNameIs("bow");
		character.herNameIs("catwoman");

		shutter();

		projectionMatrix.frustum(left, right, bottom, top, neear, faar);
	}











	void Camera::move(const int direct, const float velocity)
	{
		CAGLM::Vec3<float> v = lookAt - position;	v.Y(0);
		v = CAGLM::Vec3<float>::Normalize(v);
		CAGLM::Vec3<float> n = CAGLM::Vec3<float>::Cross(v, CAGLM::Vec3<float>(0, 1, 0));
		switch (direct)
		{
		case CAGLE_FORWARD:
			position += v * velocity;
			lookAt += v * velocity;
			break;
		case CAGLE_BACKWARD:
			position -= v * velocity;
			lookAt -= v * velocity;
			break;
		case CAGLE_LEFT:
			position += n * velocity;
			lookAt += n * velocity;
			break;
		case CAGLE_RIGHT:
			position -= n * velocity;
			lookAt -= n * velocity;
			break;
		case CAGLE_UP:
			position.Y(position.Y() + 5 * velocity);
			lookAt.Y(lookAt.Y() + 5 * velocity);
			break;
		case CAGLE_DOWN:
			position.Y(position.Y() - 5 * velocity);
			lookAt.Y(lookAt.Y() - 5 * velocity);
			break;
		default:
			throw;
		}
		shutter();
	}





	void Camera::lookAround(const int direct, const float velocity)
	{
		float theta = 10.f*M_PI / 180 * velocity;
		float x, z;

		switch (direct)
		{
		case CAGLE_LEFT:
			x = (lookAt.X() - position.X()) * cos(theta) - (lookAt.Z() - position.Z())*sin(theta) + position.X();
			z = (lookAt.X() - position.X()) * sin(theta) + (lookAt.Z() - position.Z())*cos(theta) + position.Z();
			lookAt.X(x);		lookAt.Z(z);
			break;
		case CAGLE_RIGHT:
			theta *= -1;
			x = (lookAt.X() - position.X()) * cos(theta) - (lookAt.Z() - position.Z())*sin(theta) + position.X();
			z = (lookAt.X() - position.X()) * sin(theta) + (lookAt.Z() - position.Z())*cos(theta) + position.Z();
			lookAt.X(x);		lookAt.Z(z);
			break;
		case CAGLE_UP:
			lookAt.Y(lookAt.Y() + 5 * velocity);
			break;
		case CAGLE_DOWN:
			lookAt.Y(lookAt.Y() - 5 * velocity);
			break;
		}

		yaw = CAGLM::Vec3<float>::Angle(lookAt - position, CAGLM::Vec3<float>(0, 0, 1));
		if ((lookAt - position).X() < 0) yaw *= -1;
		yaw *= 180 / M_PI;

		shutter();
	}




	void Camera::fovyUp(const float value)
	{
		fovy += value * M_PI / 180;
		if (fovy > 2.0) fovy = 2.0;
		shutter();
	}



	void Camera::fovyDown(const float value)
	{
		fovy -= value * M_PI / 180;
		if (fovy < 0.0) fovy = 0.0;
		shutter();
	}




	void Camera::projectionSwitch(const int type)
	{

		if (projectionType == PROJECTION_MAPVIEW && type == PROJECTION_MAPVIEW)
			projectionType = PROJECTION_PERSPECTIVE;
		else projectionType = type;
		projectionRefresh();
	}


	void Camera::projectionRefresh(void)
	{

		switch (projectionType)
		{

		case PROJECTION_MAPVIEW:
			viewMatrix.lookAt(CAGLM::Vec3<float>(0, 50, 0), CAGLM::Vec3<float>(0, 0, 0), CAGLM::Vec3<float>(0, 0, 1));
			viewMatrix.scalef(0.005f, 0.005f, 0.005f);
			projectionMatrix.parallel(left, right, bottom, top, neear, faar);
			break;


		case PROJECTION_PERSPECTIVE:
			viewMatrix.lookAt(position, lookAt, cameraUp);
			projectionMatrix.frustum(left, right, bottom, top, neear, faar);
			break;


		case PROJECTION_ORTHOGONAL:
			viewMatrix.lookAt(position, lookAt, cameraUp);
			projectionMatrix.parallel(left, right, bottom, top, neear, faar);
			break;

		}
	}


	void Camera::shutter()
	{
		/** Adjust the view box */
		top = -2 * neear*tan(fovy / 2);
		bottom = -top;
		right = aspect * top;
		left = -right;


		viewMatrix.scalef(size, size, size);

		/** Adjust the value of the weapon
		* so that the camera's body(chacter) can move
		* along camera's center point.*/
//		weapon.Position(position + CAGLM::Vec3<float>::Normalize(position - lookAt) * 5);
//		weapon.Yaw(yaw);
//		weapon.refresh();

//		character.Position(position + CAGLM::Vec3<float>::Normalize(position - lookAt) * 10 + CAGLM::Vec3<float>(0, -30, 0));
//		character.Yaw(yaw);
//		character.refresh();

		/** Proj and View matrix refresh */
		projectionRefresh();
	}


	Object* Camera::getWeaponObject()
	{
		return &weapon;
	}

	Object* Camera::getCharacterObject()
	{
		return &character;
	}


	void Camera::Position(CAGLM::Vec3<float> point)
	{
		position = point;
	}
	void Camera::Lookat(CAGLM::Vec3<float> vec)
	{
		lookat = vec;
	}
}


