#include "light.h"

namespace CAGLE {
	Light::Light() :pitch(0)
	{
		source.herNameIs("star");
		source.Position(CAGLM::Vec3<float>(0, 0, 20));
		source.Size(0.01f);
		source.Color(0xFF0000);
	}





	void Light::sunset(const float velocity)
	{
		float radian = pitch * M_PI / 180;

		CAGLM::Vec3<float> direct(0, -sin(radian), cos(radian));

		position += direct;
		refresh();
	}



	Object* Light::getObject()
	{
		return &source;
	}



	void Light::refresh()
	{
		source.Position(position);
		source.refresh();
	}

}