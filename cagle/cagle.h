/*************************************************/
/** @CAGLE										**/
/**   ==Chung Ang university GL Engine			**/
/**												**/
/** @Version : v1.7								**/
/** @Author : Jeong Won Cheol					**/
/** @Contact : jwch11@gmail.com					**/
/**												**/
/** @Create : 20th May 2017						**/
/** @Last Modified: 9th August 2017				**/
/**												**/
/**	@Class : Object, Camera and Light			**/
/*************************************************/



#pragma once
#include <string>

#include "caglm.h"
#include "caglemvp.h"


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

	/*******************************/
	/* Object                      */
	/*  blabla                     */
	/*******************************/
	class Object {



	public:
		/** Moving operator Funciton*/
		void forward(const float velocity);

		void around(const float velocity);



	private:
		/** Object Name */
		std::string lable;

							
		/** Local Coordinate
		* Polygon Data */
		
		int polygoncount;
		int polygoncolor;
		float* vertexdata;
		float* normaldata;
		float* uvdata;
		


		

		/** World Coordinate */
		CAGLM::Vec3 position;
		float size;
		float yaw;
	
		ModelMatrix modelMatrix;

	public:
		Object();
		


		/** ModelMatrix refersh */
		void refresh();



		/** Parsing function*/
		void dataLoad2(const std::string filename);
		void dataLoad(const std::string filename);

		void positionRotation(float turnRadius, float velocity, float x, float y, float z);





		/** Get and Set */
		AUTO_GETSET(std::string, hisNameIs, lable);
		AUTO_GETSET(std::string, herNameIs, lable);
		AUTO_GETSET(CAGLM::Vec3, Position, position);
		AUTO_GETSET2(float, X, position);
		AUTO_GETSET2(float, Y, position);
		AUTO_GETSET2(float, Z, position);
		AUTO_GETSET(float, Size, size);
		AUTO_GETSET(float, Yaw, yaw);
		AUTO_GETSET(int, Color, polygoncolor);


		/** Get */
		const float* loadNormal()													{ return normaldata; }
		const float* loadVertexPosition()											{ return vertexdata; }
		const int	 loadPolygonCount()												{ return polygoncount; }
		const float* loadModelMatrix()												{ return modelMatrix.getElement(); }
	};













	/*******************************/
	/* CAMERA                      */
	/*  blabla                     */
	/*******************************/
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
		CAGLM::Vec3 position;
		CAGLM::Vec3 lookAt;
		CAGLM::Vec3 cameraUp;
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
		Camera();

		




		/** Get and Set */
		/* If you using this, then you must have shutter */
		AUTO_GETSET(CAGLM::Vec3, Position, position);
		AUTO_GETSET(CAGLM::Vec3, LookAt, lookAt);
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
		Object* getWeaponObject();
		Object* getCharacterObject();
		const float* loadViewMatrix() const												{ return viewMatrix.getElement(); }
		const float* loadProjectionMatrix()	const										{ return projectionMatrix.getElement(); }
	};









	/*******************************/
	/* Light                       */
	/*  blabla                     */
	/*******************************/
	class Light {

	public:

		void sunset(const float velocity);


		void refresh();



	private:
		CAGLM::Vec3 position;

		/** The substance of the light */
		Object source;

		float pitch;


	public:
		Light();
		
		
		
		/** Get and Set */
		Object* getObject();
		
		AUTO_GETSET(CAGLM::Vec3, Position, position);
		AUTO_GETSET(float, Pitch, pitch);
		AUTO_GETSET2(float, X, position);
		AUTO_GETSET2(float, Y, position);
		AUTO_GETSET2(float, Z, position);
	};

}