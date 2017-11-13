/*************************************************/
/** @CAGLE Mannager								**/
/**   ==Chung Ang university GL Engine			**/
/**												**/
/** @Version : v1.2								**/
/** @Author : Jeong Won Cheol					**/
/** @Contact : jwch11@gmail.com					**/
/**												**/
/** @Create : 30th May 2017						**/
/** @Last Modified: 5th June 2017				**/
/**												**/
/**	@Class : Management							**/
/*************************************************/



#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <utility>

#include "object.h"
#include "camera.h"
#include "light.h"
#include "player.h"

namespace CAGLE {
	/** forward Declaration */
	class Object;	
	class Camera;
	class Light;
	class Player;

	class Management {
	public:
		static Management& get_instance()
		{
			static Management instance;
			return instance;
		}
		
	public:
		/***************** Object manage *******************************************************/

		bool newObject(const std::string name);

		Object* getObject(const std::string name);

		bool copyObject(const std::string dst, const std::string src, const int num=1);

		void deleteObject(const std::string name);
		/***************************************************************************************/

		
		/***************** Player manage *******************************************************/

		Player* player;

		bool getPlayer();




		/** Collision Test **/
		bool isCollision(const std::string name1, const std::string name2);
		bool isCollision(const std::string name1, const std::string name2, const int pivot);


		/** Call All */
		std::map<std::string, Object*> get_all_objects();
		/***************************************************************************************/







		/***************** Camera manage *******************************************************/
		/** Hire */
		Camera* iWannaCamera(void);


		/** Call */
		Camera* getCamera(void);
		/***************************************************************************************/







		/***************** Light manage ********************************************************/
		/** Hire */
		Light* iWannaLight(void);


		/** Call */
		Light* getLight(void);
		/***************************************************************************************/



		
		


		void refresh(void);





	private:
		Management() {}

		/** The intern Objects means base object
		* It do not draw to world.
		* Programmer hire object to base intern object
		*/

		std::map<std::string, Object*> objects;

		Camera* onlyCamera;

		Light* onlyLight;
	};

}
