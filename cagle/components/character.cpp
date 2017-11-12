#include "character.h"


namespace CAGLE {
	void Character::move(const int direct, const float velocity)
	{
		switch (direct)
		{
		case CAGLE_FORWARD:
			Position(position + lookat*velocity);
			break;
		case CAGLE_BACKWARD:
			Position(position - lookat*velocity);
			break;
		case CAGLE_LEFT:
		case CAGLE_RIGHT:
		}
	}


	void Character::Lookat(CAGLM::Vec3<float> vec)
	{
		figuare.Lookat(vec);
		eye.Lookat(vec);
		weapon.Lookat(vec);

		Position(position);
	}


	void Character::Position(CAGLM::Vec3<float> point)
	{
		figuare.Position(point);
		eye.Position(point - lookat);
		weapon.Position(point + lookat);
	}
}