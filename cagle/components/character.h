#pragma once

#include "object.h"
#include "camera.h"
#include "control.h"

namespace CAGLE {
	class Character {
	public:
		Character()
		{
			
		
		}


		void move(const int direct, const float velocity);

		void look(const int direct, const float velocity);

		void fovyUp(const float value);

		void fovyDown(const float value);



	private:
		Object figuare;
		Object weapon;
		Camera eye;
		Control control;

		CAGLM::Vec3<float> position;
		CAGLM::Vec3<float> lookat;


	public:
		Object* getWeaponObject() { return &weapon; }
		Object* getCharacterObject() { return &figuare; }
		Camera* getEye() { return &eye; }

		CAGLM::Vec3<float> Position() { return position; }

		void Position(CAGLM::Vec3<float> point);
		void Lookat(CAGLM::Vec3<float> vec);
	};



}