/*************************************************/
/** @CAGLE										**/
/**   ==Chung Ang university GL Engine			**/
/*************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "light.h"

namespace CAGLE {

	Light::Light() :pitch(0)
	{}





	void Light::sunset(const float velocity)
	{
		float radian = pitch * M_PI / 180;

		CAGLM::Vec3<float> direct(0, -sin(radian), cos(radian));

		position += direct;
	}
};