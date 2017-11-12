#pragma once

#include "..\caglm.h"
#include "object.h"
#include "mvp.h"


#define CAGLE_FORWARD 0x01
#define CAGLE_BACKWARD 0x02
#define CAGLE_LEFT 0x03
#define CAGLE_RIGHT 0x04
#define CAGLE_UP 0x05
#define CAGLE_DOWN 0x06

#define PROJECTION_PERSPECTIVE	0x0040
#define PROJECTION_ORTHOGONAL	0x0041
#define PROJECTION_MAPVIEW		0x0042 


/** Auto GET and Set Function Maker */
#define AUTO_GETSET2(TYPE2, FUNC_NAME2, PROP2) \
		TYPE2 FUNC_NAME2() const \
		{ return PROP2.FUNC_NAME2(); } \
		void FUNC_NAME2(const TYPE2 ARG2) \
		{ PROP2.FUNC_NAME2(ARG2);}

namespace CAGLE {

	class Camera {
	public:

		void move(const int direct, const float velocity);


		/** Programable Function */

		void lookAround(const int direct, const float velocity);

		void fovyUp(const float value);

		void fovyDown(const float value);

		void projectionSwitch(const int type);


		/** ViewMatrix and ProjectinoMatrix refersh */
		void shutter();





		/** System ***/
	private:
		/** Camera Coordinate */
		CAGLM::Vec3<float> position;
		CAGLM::Vec3<float> lookat;
		CAGLM::Vec3<float> cameraUp;
		float size;
		float roll, yaw, pitch;
		float fovy, aspect;
		float neear, faar;
		float left, right, bottom, top;
		bool flushMap;

		ViewMatrix viewMatrix;


		/** Homogeneous Coordinate */
		int projectionType;
		ProjectionMatrix projectionMatrix;


		void projectionRefresh(void);

		/** The substance of the camera */
		Object weapon;
		Object character;
	public:
		explicit Camera();






		/** Get and Set */
		/* If you using this, then you must have shutter */

		void Position(CAGLM::Vec3<float> point);
		void Lookat(CAGLM::Vec3<float> vec);

		AUTO_GETSET2(float, X, position);
		AUTO_GETSET2(float, Y, position);
		AUTO_GETSET2(float, Z, position);
		AUTO_GETSET(float, Size, size);
		AUTO_GETSET(float, Roll, roll);
		AUTO_GETSET(float, Yaw, yaw);
		AUTO_GETSET(float, Pitch, pitch);
		AUTO_GETSET(float, Fovy, fovy);
		AUTO_GETSET(float, Far, faar);
		AUTO_GETSET(float, Aspect, aspect);
		AUTO_GETSET(bool, FlushMap, flushMap);
		AUTO_GETSET(int, ProjectionType, projectionType);




		/** Get */
		const float* loadViewMatrix() const { return viewMatrix.getElement(); }
		const float* loadProjectionMatrix()	const { return projectionMatrix.getElement(); }

		Object* getWeaponObject();
		Object* getCharacterObject();
	};


}