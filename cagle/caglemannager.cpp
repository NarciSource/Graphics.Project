/*************************************************/
/** @CAGLE Mannager								**/
/**   ==Chung Ang university GL Engine			**/
/*************************************************/

#include <iostream>

#include "cagle.h"
#include "caglemannager.h"

namespace CAGLE {
	Object* Management::iWannaInternObject(void)
	{
		Object* newObject;
		newObject = new Object;
		internObjects.push_back(newObject);
		return newObject;
	}



	Object* Management::iWannaObject(void)
	{
		Object* newObject;
		newObject = new Object;
		objects.push_back(newObject);
		return newObject;
	}



	Object* Management::iWannaObject(const std::string internName)
	{
		std::vector<Object*>::iterator itor;
		itor = std::find_if(internObjects.begin(), internObjects.end(),
			[&](Object* object)-> bool {
			return (object->hisNameIs() == internName);
		});
		if (itor == internObjects.end()) {
			std::cout << "Don't find this object" << std::endl;
			return NULL;
		}

		Object* newObject;
		newObject = new Object(**itor);

		objects.push_back(newObject);
		return newObject;
	}

	

	Object* Management::getObject(const std::string name)
	{
		if (onlyCamera->getWeaponObject()->hisNameIs() == name)
			return onlyCamera->getWeaponObject();
		
		if (onlyLight->getObject()->herNameIs() == name)
			return onlyLight->getObject();


		std::vector<Object*>::iterator itor;
		itor = std::find_if(objects.begin(), objects.end(),
			[&](Object* object)-> bool {
			return (object->hisNameIs() == name);
		});
		if (itor == objects.end()) { //nofind
			return NULL;
		}
		return *itor;
	}




	Object* Management::getInternObject(const std::string name)
	{
		std::vector<Object*>::iterator itor;
		itor = std::find_if(internObjects.begin(), internObjects.end(),
			[&](Object* object)-> bool {
			return (object->hisNameIs() == name);
		});
		if (itor == internObjects.end()) throw;
		return *itor;
	}




	void Management::fireObject(const std::string name)
	{
		std::vector<Object*>::iterator itor;
		itor = std::find_if(objects.begin(), objects.end(),
			[&](Object* object)-> bool {
			return (object->hisNameIs() == name);
		});
		if (itor == objects.end()) throw;

		delete *itor;
		objects.erase(itor);
	}

	void Management::fireInternObject(const std::string name)
	{
		std::vector<Object*>::iterator itor;
		itor = std::find_if(internObjects.begin(), internObjects.end(),
			[&](Object* object)-> bool {
			return (object->hisNameIs() == name);
		});
		if (itor == internObjects.end()) throw;

		delete *itor;
		internObjects.erase(itor);
	}



	bool Management::isCollision(const std::string name1, const std::string name2)
	{
		Object* object1 = getObject(name1);
		Object* object2 = getObject(name2);

		if( (object1->Position() - object2->Position()).length() <10 )
			return true;
		else return false;
	}

	bool Management::isCollision(const std::string name1, const std::string name2, const int pivot)
	{
		Object* object1 = getObject(name1);
		Object* object2 = getObject(name2);

		if ((object1->Position() - object2->Position()).length() <pivot)
			return true;
		else return false;
	}



	std::vector<Object*> Management::getAllobjects()
	{
		return objects;
	}



	

	Camera* Management::iWannaCamera(void)
	{
		onlyCamera = new Camera;
		return onlyCamera;
	}


	Camera* Management::getCamera(void)
	{
		return onlyCamera;
	}




	Light* Management::iWannaLight(void)
	{
		onlyLight = new Light;
		return onlyLight;
	}


	Light* Management::getLight(void)
	{
		return onlyLight;
	}



	void Management::refresh(void)
	{
		for (auto op : objects)
		{
			op->refresh();
		}
		onlyCamera->shutter();
		onlyLight->refresh();
	
	}
	
}