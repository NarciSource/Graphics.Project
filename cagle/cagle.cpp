/*************************************************/
/** @CAGLE										**/
/**   ==Chung Ang university GL Engine			**/
/*************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "cagle.h"

namespace CAGLE {
	Object::Object() :polygoncolor(0xFFFFFF), position(CAGLM::Vec3<float>(0, 0, 0)), size(1), yaw(0) {}




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





	void Object::refresh()
	{ 
		modelMatrix.setIdentity();
		modelMatrix.scalef(size, size, size);
		modelMatrix.rotatef(yaw, 0, 1, 0);
		modelMatrix.translatev(position);
	}







	void Object::positionRotation(float turnRadius, float velocity, float x, float y, float z)
	{
		int theta = static_cast<int>(velocity / turnRadius * /*glutGet(UT_ELAPSED_TIME) /*/ 100.f) % (360);

		modelMatrix.setIdentity();
		modelMatrix.translatev(-position);
		modelMatrix.translatef(turnRadius, 0, 0);
		modelMatrix.rotatef(1.0f*theta, x, y, z);
		modelMatrix.translatef(-turnRadius, 0, 0);
		modelMatrix.translatev(position);
	}







	/** Parsing function for HOMEWORK*/
	void Object::dataLoad2(const std::string filename)
	{	/** Data parsing */
		std::ifstream fin(filename);
		if (!fin.is_open()) {
			std::cerr << "no file: " << filename << std::endl;
			return;
		}
		else {
			std::clog << "file open: " << filename << std::endl;
		}

		std::vector<CAGLM::Vec3<float>> localVertices;
		std::vector<CAGLM::Vec3<float>> localNormals;
		std::vector<CAGLM::Vec3<int>> localIndices;

		std::string token;
		int vertexcount;


		fin >> token >> token >> vertexcount;

		localVertices.assign(vertexcount, CAGLM::Vec3<float>(0,0,0));
		for (int i = 0; i < vertexcount; i++)
		{
			float x, y, z;
			fin >> x >> y >> z;
			localVertices[i] = CAGLM::Vec3<float>(x/100, y/100, z/100); // size of magic number <-want to modification
		}

		fin >> token >> token >> this->polygoncount;

		localIndices.assign(polygoncount, CAGLM::Vec3<int>(0, 0, 0));
		for (int i = 0; i < polygoncount; i++)
		{
			int x, y, z;
			fin >> x >> y >> z;
			localIndices[i] = CAGLM::Vec3<int>(x, y, z);
		}




		/** !! 
		****** Calcurate Normal Vector    ******************
		* It uses cross product to calcurate a normal vector.
		* The normal vector of each vertex is calculated
		* by weighting the angle of the surrounding plane.
		*****************************************************/
		localNormals.assign(vertexcount, CAGLM::Vec3<float>(0, 0, 0));
		for (int i = 0; i < polygoncount; i++)
		{
			CAGLM::Vec3<float> p1, p2, p3;
			CAGLM::Vec3<float> v1, v2, normalv;
			float angle;


			/** Three points on which to calcurate normal vector */
			p1 = localVertices[localIndices[i].X()];
			p2 = localVertices[localIndices[i].Y()];
			p3 = localVertices[localIndices[i].Z()];
				

				
			/** Normal Vector of first point 
			* This multiplies theta by weight.	*/
			v1 = p2 - p1;	v2 = p3 - p1;
				normalv = CAGLM::Vec3<float>::Cross(v1, v2);
				angle = CAGLM::Vec3<float>::Angle(v1, v2);
			localNormals[localIndices[i].X()] += normalv * angle;

			/* Second point */
			v1 = p3 - p2;	v2 = p1 - p2;
				normalv = CAGLM::Vec3<float>::Cross(v1, v2);
				angle = CAGLM::Vec3<float>::Angle(v1, v2);
			localNormals[localIndices[i].Y()] += normalv * angle;

			/* Third point */
			v1 = p1 - p3;	v2 = p2 - p3;
				normalv = CAGLM::Vec3<float>::Cross(v1, v2);
				angle = CAGLM::Vec3<float>::Angle(v1, v2);
			localNormals[localIndices[i].Z()] += normalv * angle;
		}
		for (auto &localNormal : localNormals)
		{
			localNormal = CAGLM::Vec3<float>::Normalize(localNormal);
		}



			

		vertexdata = new float[polygoncount * 3 * 3];
		normaldata = new float[polygoncount * 3 * 3];
		for (int i = 0; i < this->polygoncount; i++)
		{
			vertexdata[i*9 + 0] = localVertices[localIndices[i].X()].X();
			vertexdata[i*9 + 1] = localVertices[localIndices[i].X()].Y();
			vertexdata[i*9 + 2] = localVertices[localIndices[i].X()].Z();

			vertexdata[i*9 + 3] = localVertices[localIndices[i].Y()].X();
			vertexdata[i*9 + 4] = localVertices[localIndices[i].Y()].Y();
			vertexdata[i*9 + 5] = localVertices[localIndices[i].Y()].Z();

			vertexdata[i*9 + 6] = localVertices[localIndices[i].Z()].X();
			vertexdata[i*9 + 7] = localVertices[localIndices[i].Z()].Y();
			vertexdata[i*9 + 8] = localVertices[localIndices[i].Z()].Z();


			normaldata[i*9 + 0] = localNormals[localIndices[i].X()].X();
			normaldata[i*9 + 1] = localNormals[localIndices[i].X()].Y();
			normaldata[i*9 + 2] = localNormals[localIndices[i].X()].Z();

			normaldata[i*9 + 3] = localNormals[localIndices[i].Y()].X();
			normaldata[i*9 + 4] = localNormals[localIndices[i].Y()].Y();
			normaldata[i*9 + 5] = localNormals[localIndices[i].Y()].Z();

			normaldata[i*9 + 6] = localNormals[localIndices[i].Z()].X();
			normaldata[i*9 + 7] = localNormals[localIndices[i].Z()].Y();
			normaldata[i*9 + 8] = localNormals[localIndices[i].Z()].Z();
		}
	}





	


	void Object::dataLoad(const std::string filename)
	{
		std::ifstream fin(filename);
		if (!fin.is_open()) {
			std::cerr << "no file: " << filename << std::endl;
			return;
		}
		else {
			std::clog << "file open: " << filename << std::endl;
		}

		std::vector<CAGLM::Vec3<float>> localVertices;
		std::vector<CAGLM::Vec3<float>> localUvs;
		std::vector<CAGLM::Vec3<float>> localNormals;
		std::vector<unsigned int> localVertexIndices;
		std::vector<unsigned int> localUvIndices;
		std::vector<unsigned int> localNormalIndices;

		std::string line;
		const static std::regex vPattern{ R"(v\s(-?\d+.?\d*)\s(-?\d+.?\d*)\s(-?\d+.?\d*))" }; // (x y z)
		const static std::regex vtPattern{ R"(vt\s(-?\d+.?\d*)\s(-?\d+.?\d*)(?:\s(-?\d+.?\d*)){0,1})" }; // (x y z) or (x y)
		const static std::regex vnPattern{ R"(vn\s(-?\d+.?\d*)\s(-?\d+.?\d*)\s(-?\d+.?\d*))" }; // (x y z)
		const static std::regex fPattern{ R"(f\s(\d+)/(\d)*/(\d+)\s(\d+)/(\d)*/(\d+)\s(\d+)/(\d)*/(\d+))" }; //(x1/y1/z1 x2/y2/z2 x3/y3/z3) or (x1//z1 x2//z2 x3//z3)
		std::smatch m;

		polygoncount = 0;		
		while (std::getline(fin,line))
		{
			std::regex_search(line, m, vPattern);
			if (m[0].matched)
			{
				localVertices.push_back(CAGLM::Vec3<float>(std::stof(m[1]), std::stof(m[2]), std::stof(m[3])));
				continue;
			}

			std::regex_search(line, m, vtPattern);
			if (m[0].matched)
			{
				if(m[3].matched)
					localUvs.push_back(CAGLM::Vec3<float>(std::stof(m[1]), std::stof(m[2]), std::stof(m[3])));
				else
					localUvs.push_back(CAGLM::Vec3<float>(std::stof(m[1]), std::stof(m[2]), 0.f));
				continue;
			}

			std::regex_search(line, m, vnPattern);
			if (m[0].matched)
			{
				localNormals.push_back(CAGLM::Vec3<float>(std::stof(m[1]), std::stof(m[2]), std::stof(m[3])));
				continue;
			}

			std::regex_search(line, m, fPattern);
			if (m[0].matched)
			{
				localVertexIndices.push_back(std::stoi(m[1]) - 1);
				localVertexIndices.push_back(std::stoi(m[4]) - 1);
				localVertexIndices.push_back(std::stoi(m[7]) - 1);

				if (m[2].matched)
				{
					localUvIndices.push_back(std::stoi(m[2]) - 1);
					localUvIndices.push_back(std::stoi(m[5]) - 1);
					localUvIndices.push_back(std::stoi(m[8]) - 1);
				}
				else {
					localUvIndices.push_back(0);
					localUvIndices.push_back(0);
					localUvIndices.push_back(0);
				}
				localNormalIndices.push_back(std::stoi(m[3])-1);				
				localNormalIndices.push_back(std::stoi(m[6])-1);				
				localNormalIndices.push_back(std::stoi(m[9])-1);

				polygoncount++;
				continue;
			}

		}
		
		
		vertexdata	= new float[polygoncount * 3 * 3];
		normaldata	= new float[polygoncount * 3 * 3];
		uvdata		= new float[polygoncount * 3 * 3];
		for (int i = 0; i < this->polygoncount*3; i++)
		{
			vertexdata[i*3 + 0] = localVertices[localVertexIndices[i]].X();
			vertexdata[i*3 + 1] = localVertices[localVertexIndices[i]].Y();
			vertexdata[i*3 + 2] = localVertices[localVertexIndices[i]].Z();

			normaldata[i*3 + 0] = localNormals[localNormalIndices[i]].X();
			normaldata[i*3 + 1] = localNormals[localNormalIndices[i]].Y();
			normaldata[i*3 + 2] = localNormals[localNormalIndices[i]].Z();

			if (localUvs.empty()) continue;
			
			uvdata[i*3 + 0]		= localUvs[localUvIndices[i]].X();
			uvdata[i*3 + 1]		= localUvs[localUvIndices[i]].Y();
			uvdata[i*3 + 2]		= localUvs[localUvIndices[i]].Z();
		}
		
	}







	Camera::Camera() : size(1), cameraUp(CAGLM::Vec3<float>(0,1,0)),
						roll(0), yaw(0), pitch(0), fovy(1),
						aspect(2.0), neear(0.1f), faar(100.f),
						projectionType(PROJECTION_PERSPECTIVE), flushMap(false)
	{
		weapon.hisNameIs("bow");
		character.herNameIs("catwoman");

		shutter();

		projectionMatrix.frustum(left, right, bottom, top, neear, faar);
	}











	void Camera::move(const int direct, const float velocity)
	{
		CAGLM::Vec3<float> v = lookAt - position;	v.Y(0);
		v = CAGLM::Vec3<float>::Normalize(v);
		CAGLM::Vec3<float> n = CAGLM::Vec3<float>::Cross(v, CAGLM::Vec3<float>(0, 1, 0));
		switch (direct)
		{
		case CAGLE_FORWARD:
			position += v * velocity;
			lookAt += v * velocity;
			break;
		case CAGLE_BACKWARD:
			position -= v * velocity;
			lookAt -= v * velocity;
			break;
		case CAGLE_LEFT:
			position += n * velocity;
			lookAt += n * velocity;
			break;
		case CAGLE_RIGHT:
			position -= n * velocity;
			lookAt -= n * velocity;
			break;
		case CAGLE_UP:
			position.Y(position.Y() + 5 * velocity);
			lookAt.Y(lookAt.Y() + 5 * velocity);
			break;
		case CAGLE_DOWN:
			position.Y(position.Y() - 5*velocity);
			lookAt.Y(lookAt.Y() - 5 * velocity);
			break;
		default :
			throw;
		}
		shutter();
	}





	void Camera::lookAround(const int direct, const float velocity)
	{		
		float theta = 10.f*M_PI / 180 * velocity;
		float x, z;

		switch (direct)
		{
		case CAGLE_LEFT:
			x = (lookAt.X() - position.X()) * cos(theta) - (lookAt.Z() - position.Z())*sin(theta) + position.X();
			z = (lookAt.X() - position.X()) * sin(theta) + (lookAt.Z() - position.Z())*cos(theta) + position.Z();
			lookAt.X(x);		lookAt.Z(z);
			break;
		case CAGLE_RIGHT:
			theta *= -1;
			x = (lookAt.X() - position.X()) * cos(theta) - (lookAt.Z() - position.Z())*sin(theta) + position.X();
			z = (lookAt.X() - position.X()) * sin(theta) + (lookAt.Z() - position.Z())*cos(theta) + position.Z();
			lookAt.X(x);		lookAt.Z(z);
			break;
		case CAGLE_UP:
			lookAt.Y(lookAt.Y() + 5 * velocity);
			break;
		case CAGLE_DOWN:
			lookAt.Y(lookAt.Y() - 5 * velocity);
			break;
		}

		yaw = CAGLM::Vec3<float>::Angle(lookAt - position, CAGLM::Vec3<float>(0, 0, 1));
		if ((lookAt - position).X() < 0) yaw *= -1;
		yaw *= 180 / M_PI;
		
		shutter();
	}




	void Camera::fovyUp(const float value)
	{
		fovy += value * M_PI / 180;
		if (fovy > 2.0) fovy = 2.0;
		shutter();
	}
	


	void Camera::fovyDown(const float value)
	{
		fovy -= value * M_PI / 180;
		if (fovy < 0.0) fovy = 0.0;
		shutter();
	}




	void Camera::projectionSwitch(const int type)
	{

		if (projectionType == PROJECTION_MAPVIEW && type == PROJECTION_MAPVIEW)
			projectionType = PROJECTION_PERSPECTIVE;
		else projectionType = type;
		projectionRefresh();
	}
	

	void Camera::projectionRefresh(void)
	{
		
		switch (projectionType)
		{

		case PROJECTION_MAPVIEW:
			viewMatrix.lookAt(CAGLM::Vec3<float>(0, 50, 0), CAGLM::Vec3<float>(0, 0, 0), CAGLM::Vec3<float>(0, 0, 1));
			viewMatrix.scalef(0.005f, 0.005f, 0.005f);
			projectionMatrix.parallel(left, right, bottom, top, neear, faar);
			break;


		case PROJECTION_PERSPECTIVE:
			viewMatrix.lookAt(position, lookAt, cameraUp);
			projectionMatrix.frustum(left, right, bottom, top, neear, faar);
			break;


		case PROJECTION_ORTHOGONAL:
			viewMatrix.lookAt(position, lookAt, cameraUp);
			projectionMatrix.parallel(left, right, bottom, top, neear, faar);
			break;

		}
	}


	void Camera::shutter()
	{
		/** Adjust the view box */
		top = -2 * neear*tan(fovy / 2);
		bottom = -top;
		right = aspect * top;
		left = -right;
		

		viewMatrix.scalef(size, size, size);

		/** Adjust the value of the weapon
		* so that the camera's body(chacter) can move
		* along camera's center point.*/
		weapon.Position(position + CAGLM::Vec3<float>::Normalize(position - lookAt) * 5);
		weapon.Yaw(yaw);
		weapon.refresh();

		character.Position(position + CAGLM::Vec3<float>::Normalize(position - lookAt) * 10 + CAGLM::Vec3<float>(0,-30,0));
		character.Yaw(yaw);
		character.refresh();

		/** Proj and View matrix refresh */
		projectionRefresh();
	}


	Object* Camera::getWeaponObject()
	{
		return &weapon;
	}

	Object* Camera::getCharacterObject()
	{
		return &character;
	}



	Light::Light():pitch(0)
	{
		source.herNameIs("star");
		source.Position(CAGLM::Vec3<float>(0,0,20));
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
};