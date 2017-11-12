#pragma once
#include <string>

#include "..\caglm.h"
#include "mvp.h"
#include "modelData.h"

/** Auto GET and Set Function Maker */
#define AUTO_GETSET2(TYPE2, FUNC_NAME2, PROP2) \
		TYPE2 FUNC_NAME2() const \
		{ return PROP2.FUNC_NAME2(); } \
		void FUNC_NAME2(const TYPE2 ARG2) \
		{ PROP2.FUNC_NAME2(ARG2);}


namespace CAGLE {

	class Object {

	public:
		/** Moving operator Funciton*/
		void move(const int direct, const float velocity);

		void look(const int direct, const float velocity);

		void forward(const float velocity);

		void around(const float velocity);



	private:
		/** Object Name */
		std::string lable;


		/** Local Coordinate
		* Polygon Data */
		ModelData modelData;


		/** World Coordinate */
		ModelMatrix modelMatrix;
		CAGLM::Vec3<float> position;
		CAGLM::Vec3<float> lookat;
		float size;
		float yaw;

	public:
		explicit Object();

		
		void Position(CAGLM::Vec3<float> point);
		void Lookat(CAGLM::Vec3<float> vec);
		

		/** ModelMatrix refersh */
		void refresh();


		void dataLoad2(const std::string filename)
		{
			modelData.dataLoad2(filename);
		}
		void dataLoad(const std::string filename)
		{
			modelData.dataLoad(filename);
		}

		/** Get and Set */
		AUTO_GETSET(std::string, hisNameIs, lable);
		AUTO_GETSET(std::string, herNameIs, lable);
		AUTO_GETSET(CAGLM::Vec3<float>, Position, position);
		AUTO_GETSET2(float, X, position);
		AUTO_GETSET2(float, Y, position);
		AUTO_GETSET2(float, Z, position);
		AUTO_GETSET(float, Size, size);
		AUTO_GETSET(float, Yaw, yaw);
		AUTO_GETSET(int, Color, modelData.polygoncolor);


		/** Get */
		const float* loadNormal() { return modelData.normaldata; }
		const float* loadVertexPosition() { return modelData.vertexdata; }
		const int	 loadPolygonCount() { return modelData.polygoncount; }
		const float* loadModelMatrix() { return modelMatrix.getElement(); }
	};
}