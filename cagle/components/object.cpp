#include "object.h"

namespace CAGLE {
	Object::Object() :position(CAGLM::Vec3<float>(0, 0, 0)), size(1), yaw(0)
	{
		modelData.polygoncolor = 0xFFFFFF;
	}




	void Object::forward(const float velocity)
	{
		float radian = yaw * M_PI / 180.f;

		CAGLM::Vec3<float> direct(sin(radian), 0, cos(radian));

		position += direct*velocity;
		refresh();
	}


	void Object::around(const float velocity)
	{
		yaw += velocity;
		refresh();
	}



	void Object::Position(CAGLM::Vec3<float> point)
	{
		position = point;
	}
	void Object::Lookat(CAGLM::Vec3<float> vec)
	{
		lookat = vec;
	}

	void Object::refresh()
	{
		modelMatrix.setIdentity();
		modelMatrix.scalef(size, size, size);
		modelMatrix.rotatef(yaw, 0, 1, 0);
		modelMatrix.translatev(position);
	}
}