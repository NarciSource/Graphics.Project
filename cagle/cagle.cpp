/*************************************************/
/** @CAGLE										**/
/**   ==Chung Ang university GL Engine			**/
/*************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include "cagle.h"

namespace CAGLE {
	Object::Object() :polygoncolor(0xFFFFFF), position(CAGLM::Vec3(0, 0, 0)), size(1), yaw(0) {}




	void Object::forward(const float _velocity)
	{
		float radian = yaw * M_PI / 180;

		CAGLM::Vec3 direct(sin(radian), 0, cos(radian));

		position += direct*_velocity;
		refresh();
	}


	void Object::around(const float _velocity)
	{
		yaw += _velocity;
		refresh();
	}





	void Object::refresh()
	{ 
		modelMatrix.setIdentity();
		modelMatrix.scalef(size, size, size);
		modelMatrix.rotatef(yaw, 0, 1, 0);
		modelMatrix.translatev(position);
	}







	void Object::positionRotation(float _turnRadius, float _velocity, float _x, float _y, float _z)
	{
		int theta = (int)(_velocity / _turnRadius * /*glutGet(UT_ELAPSED_TIME) /*/ 100.f) % (360);

		modelMatrix.setIdentity();
		modelMatrix.translatev(-position);
		modelMatrix.translatef(_turnRadius, 0, 0);
		modelMatrix.rotatef(1.0f*theta, _x, _y, _z);
		modelMatrix.translatef(-_turnRadius, 0, 0);
		modelMatrix.translatev(position);
	}







	/** Parsing function for HOMEWORK*/
	void Object::dataLoad2(const std::string _filename)
	{	/** Data parsing */
		std::ifstream fin;	fin.open(_filename);


		CAGLM::Vec3* localVertices;
		CAGLM::Vec3* localNormals;		
		CAGLM::Vec3* localIndices;


		
		char token[10]; 
		int vertexcount;

		if (fin.is_open() == false) {
			std::cout << "no file" << std::endl;
		}
		else {
			fin >> token >> token >> vertexcount;

			localVertices = new CAGLM::Vec3[vertexcount];
			for (int i = 0; i < vertexcount; i++)
			{
				float x, y, z;
				fin >> x >> y >> z;
				localVertices[i](x/100, y/100, z/100);
			}

			fin >> token >> token >> this->polygoncount;

			localIndices = new CAGLM::Vec3[polygoncount];
			for (int i = 0; i < polygoncount; i++)
			{
				float x, y, z;
				fin >> x >> y >> z;
				localIndices[i](x, y, z);
			}




			/** !! 
			****** Calcurate Normal Vector    ******************
			* It uses cross product to calcurate a normal vector.
			* The normal vector of each vertex is calculated
			* by weighting the angle of the surrounding plane.
			*****************************************************/
			localNormals = new CAGLM::Vec3[vertexcount];
			for (int i = 0; i < vertexcount; i++) //initailize
			{
				localNormals[i] = CAGLM::Vec3(0, 0, 0);
			}
			for (int i = 0; i < polygoncount; i++)
			{
				CAGLM::Vec3 p1, p2, p3;
				CAGLM::Vec3 v1, v2, normalv;
				float angle;


				/** Three points on which to calcurate normal vector */
				p1 = localVertices[(int)localIndices[i].X()];
				p2 = localVertices[(int)localIndices[i].Y()];
				p3 = localVertices[(int)localIndices[i].Z()];
				

				
				/** Normal Vector of first point 
				* This multiplies theta by weight.	*/
				v1 = p2 - p1;	v2 = p3 - p1;
					normalv = CAGLM::Vec3::Cross(v1, v2);
					angle = CAGLM::Vec3::Angle(v1, v2);
				localNormals[(int)localIndices[i].X()] += normalv * angle;

				/* Second point */
				v1 = p3 - p2;	v2 = p1 - p2;
					normalv = CAGLM::Vec3::Cross(v1, v2);
					angle = CAGLM::Vec3::Angle(v1, v2);
				localNormals[(int)localIndices[i].Y()] += normalv * angle;

				/* Third point */
				v1 = p1 - p3;	v2 = p2 - p3;
					normalv = CAGLM::Vec3::Cross(v1, v2);
					angle = CAGLM::Vec3::Angle(v1, v2);
				localNormals[(int)localIndices[i].Z()] += normalv * angle;
			}
			for (int i = 0; i < vertexcount; i++) // normalize
			{
				localNormals[i] = CAGLM::Vec3::Normalize(localNormals[i]);
			}



			

			vertexdata = new float[polygoncount * 3 * 3];
			normaldata = new float[polygoncount * 3 * 3];
			for (int i = 0; i < this->polygoncount; i++)
			{
				vertexdata[i*9 + 0] = localVertices[(int)localIndices[i].X()].X();
				vertexdata[i*9 + 1] = localVertices[(int)localIndices[i].X()].Y();
				vertexdata[i*9 + 2] = localVertices[(int)localIndices[i].X()].Z();

				vertexdata[i*9 + 3] = localVertices[(int)localIndices[i].Y()].X();
				vertexdata[i*9 + 4] = localVertices[(int)localIndices[i].Y()].Y();
				vertexdata[i*9 + 5] = localVertices[(int)localIndices[i].Y()].Z();

				vertexdata[i*9 + 6] = localVertices[(int)localIndices[i].Z()].X();
				vertexdata[i*9 + 7] = localVertices[(int)localIndices[i].Z()].Y();
				vertexdata[i*9 + 8] = localVertices[(int)localIndices[i].Z()].Z();


				normaldata[i*9 + 0] = localNormals[(int)localIndices[i].X()].X();
				normaldata[i*9 + 1] = localNormals[(int)localIndices[i].X()].Y();
				normaldata[i*9 + 2] = localNormals[(int)localIndices[i].X()].Z();

				normaldata[i*9 + 3] = localNormals[(int)localIndices[i].Y()].X();
				normaldata[i*9 + 4] = localNormals[(int)localIndices[i].Y()].Y();
				normaldata[i*9 + 5] = localNormals[(int)localIndices[i].Y()].Z();

				normaldata[i*9 + 6] = localNormals[(int)localIndices[i].Z()].X();
				normaldata[i*9 + 7] = localNormals[(int)localIndices[i].Z()].Y();
				normaldata[i*9 + 8] = localNormals[(int)localIndices[i].Z()].Z();
			}

		}
		fin.close();
	}





	


	void Object::dataLoad(const std::string _filename)
	{
		FILE* fin = fopen(_filename.c_str(), "r");
		
		std::vector<CAGLM::Vec3> localVertices;
		std::vector<CAGLM::Vec3> localUvs;
		std::vector<CAGLM::Vec3> localNormals;
		std::vector<unsigned int> localVertexIndices;
		std::vector<unsigned int> localUvIndices;
		std::vector<unsigned int> localNormalIndices;
		char type[20];

		polygoncount = 0;
		while (fin != NULL)
		{
			float x = 0.f, y = 0.f, z = 0.f;
			if (fscanf(fin, "%s", &type) == EOF) break;

			if (type[0] == 'v' && type[1] == 't')
			{
				fscanf(fin, "%f %f %f", &x, &y, &z);
				localUvs.push_back(CAGLM::Vec3(x, y, z));
			}
			else if (type[0] == 'v' && type[1] == 'n')
			{
				fscanf(fin, "%f %f %f", &x, &y, &z);
				localNormals.push_back(CAGLM::Vec3(x, y, z));
			}
			else if (type[0] == 'v')
			{
				fscanf(fin, "%f %f %f", &x, &y, &z);
				localVertices.push_back(CAGLM::Vec3(x, y, z));
			}
			else if (type[0] == 'f')
			{
				int x=0, y=0, z=0;
				fscanf(fin, "%d/%d/%d", &x, &y, &z);
				localVertexIndices.push_back(x-1);	localUvIndices.push_back(y-1);	localNormalIndices.push_back(z-1); 
				fscanf(fin, "%d/%d/%d", &x, &y, &z);
				localVertexIndices.push_back(x-1);	localUvIndices.push_back(y-1);	localNormalIndices.push_back(z-1); 
				fscanf(fin, "%d/%d/%d", &x, &y, &z);
				localVertexIndices.push_back(x-1);	localUvIndices.push_back(y-1);	localNormalIndices.push_back(z-1);
				polygoncount++;
			}
			else {
				char buf[100];	// pass
				fgets(buf, 100, fin);
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

			uvdata[i*3 + 0]		= localUvs[localUvIndices[i]].X();
			uvdata[i*3 + 1]		= localUvs[localUvIndices[i]].Y();
			uvdata[i*3 + 2]		= localUvs[localUvIndices[i]].Z();
		}


		fclose(fin);
	}
	




	void Object::dataLoad3(const std::string _filename)
	{
		FILE* fin = fopen(_filename.c_str(), "r");

		std::vector<CAGLM::Vec3> localVertices;
		std::vector<CAGLM::Vec3> localNormals;
		std::vector<unsigned int> localVertexIndices;
		std::vector<unsigned int> localNormalIndices;
		char type[20];

		polygoncount = 0;
		while (fin != NULL)
		{
			float x = 0.f, y = 0.f, z = 0.f;
			if (fscanf(fin, "%s", &type) == EOF) break;

			else if (type[0] == 'v' && type[1] == 'n')
			{
				fscanf(fin, "%f %f %f", &x, &y, &z);
				localNormals.push_back(CAGLM::Vec3(x, y, z));
			}
			else if (type[0] == 'v')
			{
				fscanf(fin, "%f %f %f", &x, &y, &z);
				localVertices.push_back(CAGLM::Vec3(x, y, z));
			}
			else if (type[0] == 'f')
			{
				int x = 0, y = 0;
				fscanf(fin, "%d//%d", &x, &y);
				localVertexIndices.push_back(x - 1);	localNormalIndices.push_back(y - 1);
				fscanf(fin, "%d//%d", &x, &y);
				localVertexIndices.push_back(x - 1);	localNormalIndices.push_back(y - 1);
				fscanf(fin, "%d//%d", &x, &y);
				localVertexIndices.push_back(x - 1);	localNormalIndices.push_back(y - 1);
				polygoncount++;
			}
			else {
				char buf[100];	// pass
				fgets(buf, 100, fin);
			}
		}


		vertexdata = new float[polygoncount * 3 * 3];
		normaldata = new float[polygoncount * 3 * 3];
		for (int i = 0; i < this->polygoncount * 3; i++)
		{

			vertexdata[i * 3 + 0] = localVertices[localVertexIndices[i]].X();
			vertexdata[i * 3 + 1] = localVertices[localVertexIndices[i]].Y();
			vertexdata[i * 3 + 2] = localVertices[localVertexIndices[i]].Z();

			normaldata[i * 3 + 0] = localNormals[localNormalIndices[i]].X();
			normaldata[i * 3 + 1] = localNormals[localNormalIndices[i]].Y();
			normaldata[i * 3 + 2] = localNormals[localNormalIndices[i]].Z();
		}


		fclose(fin);
	}






	Camera::Camera() : size(1), cameraUp(CAGLM::Vec3(0,1,0)),
						roll(0), yaw(0), pitch(0), fovy(1),
						aspect(2.0), neear(0.1f), faar(100.f),
						projectionType(PROJECTION_PERSPECTIVE), flushMap(false)
	{
		weapon.hisNameIs("bow");
		character.herNameIs("catwoman");

		shutter();

		projectionMatrix.frustum(left, right, bottom, top, neear, faar);
	}











	void Camera::move(const int _direct, const float _velocity)
	{
		CAGLM::Vec3 v = lookAt - position;	v.Y(0);
		v = CAGLM::Vec3::Normalize(v);
		CAGLM::Vec3 n = CAGLM::Vec3::Cross(v, CAGLM::Vec3(0, 1, 0));
		switch (_direct)
		{
		case CAGLE_FORWARD:
			position += v * _velocity;
			lookAt += v * _velocity;
			break;
		case CAGLE_BACKWARD:
			position -= v * _velocity;
			lookAt -= v * _velocity;
			break;
		case CAGLE_LEFT:
			position += n * _velocity;
			lookAt += n * _velocity;
			break;
		case CAGLE_RIGHT:
			position -= n * _velocity;
			lookAt -= n * _velocity;
			break;
		case CAGLE_UP:
			position.Y(position.Y() + 5 * _velocity);
			lookAt.Y(lookAt.Y() + 5 * _velocity);
			break;
		case CAGLE_DOWN:
			position.Y(position.Y() - 5*_velocity);
			lookAt.Y(lookAt.Y() - 5 * _velocity);
			break;
		default :
			throw;
		}
		shutter();
	}





	void Camera::lookAround(const int _direct, const float _velocity)
	{		
		float theta = 10.f*M_PI / 180 * _velocity;
		float x, z;

		switch (_direct)
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
			lookAt.Y(lookAt.Y() + 5 * _velocity);
			break;
		case CAGLE_DOWN:
			lookAt.Y(lookAt.Y() - 5 * _velocity);
			break;
		}

		yaw = CAGLM::Vec3::Angle(lookAt - position, CAGLM::Vec3(0, 0, 1));
		if ((lookAt - position).X() < 0) yaw *= -1;
		yaw *= 180 / M_PI;
		
		shutter();
	}




	void Camera::fovyUp(const float _value)
	{
		fovy += (float)(_value * M_PI / 180);
		if (fovy > 2.0) fovy = 2.0;
		shutter();
	}
	


	void Camera::fovyDown(const float _value)
	{
		fovy -= (float)(_value * M_PI / 180);
		if (fovy < 0.0) fovy = 0.0;
		shutter();
	}




	void Camera::projectionSwitch(const int _type)
	{

		if (projectionType == PROJECTION_MAPVIEW && _type == PROJECTION_MAPVIEW)
			projectionType = PROJECTION_PERSPECTIVE;
		else projectionType = _type;
		projectionRefresh();
	}
	

	void Camera::projectionRefresh(void)
	{
		
		switch (projectionType)
		{


		case PROJECTION_MAPVIEW:
			viewMatrix.lookAt(CAGLM::Vec3(0, 50, 0), CAGLM::Vec3(0, 0, 0), CAGLM::Vec3(0, 0, 1));
			viewMatrix.scalef(0.005, 0.005, 0.005);
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
		weapon.Position(position + CAGLM::Vec3::Normalize(position - lookAt) * 5);
		weapon.Yaw(yaw);
		weapon.refresh();

		character.Position(position + CAGLM::Vec3::Normalize(position - lookAt) * 10 + CAGLM::Vec3(0,-30,0));
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
		source.Position(CAGLM::Vec3(0,0,20));
		source.Size(0.01f);
		source.Color(0xFF0000);
	}





	void Light::sunset(const float _velocity)
	{
		float radian = pitch * M_PI / 180;

		CAGLM::Vec3 direct(0, -sin(radian), cos(radian));

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