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
#include "mvp.h"

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
		CAGLM::Vec3<float> position;
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
		AUTO_GETSET(CAGLM::Vec3<float>, Position, position);
		AUTO_GETSET2(float, X, position);
		AUTO_GETSET2(float, Y, position);
		AUTO_GETSET2(float, Z, position);
		AUTO_GETSET(float, Size, size);
		AUTO_GETSET(float, Yaw, yaw);
		AUTO_GETSET(int, Color, polygoncolor);


		/** Get */
		const float* loadNormal() { return normaldata; }
		const float* loadVertexPosition() { return vertexdata; }
		const int	 loadPolygonCount() { return polygoncount; }
		const float* loadModelMatrix() { return modelMatrix.getElement(); }
	};





}