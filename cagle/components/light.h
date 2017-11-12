#pragma once

#include "object.h"

namespace CAGLE {
	class Light {

	public:

		void sunset(const float velocity);


		void refresh();



	private:
		CAGLM::Vec3<float> position;

		/** The substance of the light */
		Object source;

		float pitch;


	public:
		explicit Light();



		/** Get and Set */
		Object* getObject();

		AUTO_GETSET(CAGLM::Vec3<float>, Position, position);
		AUTO_GETSET(float, Pitch, pitch);
		AUTO_GETSET2(float, X, position);
		AUTO_GETSET2(float, Y, position);
		AUTO_GETSET2(float, Z, position);
	};

}