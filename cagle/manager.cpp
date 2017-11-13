/*************************************************/
/** @CAGLE Mannager								**/
/**   ==Chung Ang university GL Engine			**/
/*************************************************/

#include <iostream>

#include "manager.h"

namespace CAGLE {

	bool Management::newObject(const std::string name)
	{
		auto ret = objects.insert({ name,nullptr });
		if (ret.second)
		{
			ret.first->second = new Object();
			return true;
		}
		else { // overlap			
			return false;
		}
	}

	Object* Management::getObject(const std::string name)
	{
		if (objects.find(name) != objects.end())
		{
			return objects[name];
		}
		else {
			return nullptr;
		}
	}

	bool Management::copyObject(const std::string dst, const std::string src, const int num)
	{
		Object* src_object = getObject(src);
		if (src_object == nullptr)
		{
			std::cout << "Copy error, src isn't exist" << std::endl;
			return false;
		}

		for (int i = 0; i < num; i++)
		{
			std::string each_name;
			if (num == 1)
			{
				each_name = dst;
			}
			else {
				each_name = dst + std::to_string(i);
			}

			auto ret = objects.insert({ each_name,nullptr });
			if (ret.second)
			{
				ret.first->second = new Object(*src_object);
			}
			else {
				std::cout << "Copy error, dst is exist" << std::endl;
				return false;
			}
		}
		return true;
	}


	void Management::deleteObject(const std::string name)
	{
		auto it = objects.find(name);
		if (it != objects.end())
		{
			delete it->second;
			objects.erase(it);
		}
	}


	bool Management::getPlayer()
	{
		if (player == nullptr)
		{
			player = new Player();
		}

		return player;
	}

	


/*

	Object* Management::iWannaInternObject(void)
	{
		Object* newObject;
		newObject = new Object;
		internObjects.push_back(std::make_pair(newObject,0));
		return newObject;
	}



	Object* Management::iWannaObject(void)
	{
		Object* newObject;
		newObject = new Object;
		objects.push_back(newObject);
		return newObject;
	}



	Object* Management::iWannaObject(const std::string internName, const int num)
	{
		auto itor = std::find_if(internObjects.begin(), internObjects.end(),
			[&](std::pair<Object*,int> object)-> bool {
			return (object.first->hisNameIs() == internName);
		});
		if (itor == internObjects.end()) {
			std::cout << "Don't find this object" << std::endl;
			return nullptr;
		}

		Object* internObject = itor->first;
		int& existingInternNum = itor->second;

		for (int i = 0; i < num; i++)
		{
			Object* newObject;
			newObject = new Object(*internObject);
			newObject->herNameIs(internName + std::to_string(existingInternNum++));

			objects.push_back(newObject);
		}
		if (num == 1) {
			return objects.back();
		}
		else {
			return nullptr;
		}
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
			return nullptr;
		}
		return *itor;
	}
/*



	Object* Management::getInternObject(const std::string name)
	{
		auto itor = std::find_if(internObjects.begin(), internObjects.end(),
			[&](std::pair<Object*,int> object)-> bool {
			return (object.first->hisNameIs() == name);
		});
		if (itor == internObjects.end()) throw;
		return itor->first;
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
		auto itor = std::find_if(internObjects.begin(), internObjects.end(),
			[&](std::pair<Object*,int> object)-> bool {
			return (object.first->hisNameIs() == name);
		});
		if (itor == internObjects.end()) throw;

		delete itor->first;
		internObjects.erase(itor);
	}

	*/

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

	std::map<std::string, Object*> Management::get_all_objects()
	{
		return objects;
	}

/*	std::vector<Object*> Management::getAllobjects()
	{
		return objects;
	}
*/


	

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
		for (auto const& each : objects)
		{
			each.second->refresh();
		}
		/*
		for (auto op : objects)
		{
			op->refresh();
		}*/
		onlyCamera->shutter();
		onlyLight->refresh();
	
	}
	
}