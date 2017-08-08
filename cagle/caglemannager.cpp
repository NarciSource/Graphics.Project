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



	Object* Management::iWannaObject(const std::string _internName)
	{
		std::vector<Object*>::iterator itor;
		itor = std::find_if(internObjects.begin(), internObjects.end(),
			[&](Object* _object)-> bool {
			return (_object->hisNameIs() == _internName);
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

	

	Object* Management::getObject(const std::string _name)
	{
		if (onlyCamera->getWeaponObject()->hisNameIs() == _name)
			return onlyCamera->getWeaponObject();
		
		if (onlyLight->getObject()->herNameIs() == _name)
			return onlyLight->getObject();


		std::vector<Object*>::iterator itor;
		itor = std::find_if(objects.begin(), objects.end(),
			[&](Object* _object)-> bool {
			return (_object->hisNameIs() == _name);
		});
		if (itor == objects.end()) { //nofind
			return NULL;
		}
		return *itor;
	}




	Object* Management::getInternObject(const std::string _name)
	{
		std::vector<Object*>::iterator itor;
		itor = std::find_if(internObjects.begin(), internObjects.end(),
			[&](Object* _object)-> bool {
			return (_object->hisNameIs() == _name);
		});
		if (itor == internObjects.end()) throw;
		return *itor;
	}




	void Management::fireObject(const std::string _name)
	{
		std::vector<Object*>::iterator itor;
		itor = std::find_if(objects.begin(), objects.end(),
			[&](Object* _object)-> bool {
			return (_object->hisNameIs() == _name);
		});
		if (itor == objects.end()) throw;

		delete *itor;
		objects.erase(itor);
	}

	void Management::fireInternObject(const std::string _name)
	{
		std::vector<Object*>::iterator itor;
		itor = std::find_if(internObjects.begin(), internObjects.end(),
			[&](Object* _object)-> bool {
			return (_object->hisNameIs() == _name);
		});
		if (itor == internObjects.end()) throw;

		delete *itor;
		internObjects.erase(itor);
	}



	bool Management::isCollision(const std::string _name1, const std::string _name2)
	{
		Object* object1 = getObject(_name1);
		Object* object2 = getObject(_name2);

		if( (object1->Position() - object2->Position()).length() <10 )
			return true;
		else return false;
	}

	bool Management::isCollision(const std::string _name1, const std::string _name2, const int _pivot)
	{
		Object* object1 = getObject(_name1);
		Object* object2 = getObject(_name2);

		if ((object1->Position() - object2->Position()).length() <_pivot)
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