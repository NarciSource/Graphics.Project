#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

#include "main.hpp"
#include "json.h"

using Json = nlohmann::json;

GLint windowSizeX = 2048, windowSizeY = 1024;
int shadingType= typePhong;

CAGLE::Management gManager = CAGLE::Management::get_instance();

void main(int argc, char* argv[]) {

	/** glut, windows setting */
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowSizeX, windowSizeY);
	glutCreateWindow("GAME");

	/** gl setting => gl.cpp */
	myGLInit();


	/** set components */
	componentInit();


	/** Render => gl.cpp **/
	glutDisplayFunc(render);


	

	/******** Handler => handler.cpp **********/
	glutReshapeFunc(changeSize);	
//	glutIdleFunc(idle);
	glutTimerFunc(30, idle, 1);
	glutKeyboardFunc(keyboardHandler);
	glutSpecialFunc(specialKeyboardHandler);
	glutMouseFunc(mouseClickHandler);
	glutPassiveMotionFunc(mouseMoveHandler);
	/****************************************/

	ShowCursor(false);
	glutMainLoop();
}


/****  Set Init position  ****/
void componentInit()
{
	/** make Terrain */
	gManager.newTerrain("heightmap.bmp");

	Json save;
	std::ifstream in("data.json");
	in >> save;

	/** make Camera */
	for (auto it = save["c"].begin(); it != save["c"].end(); it++)
	{
		std::string name = it.key();
		Json list = it.value();

		auto& camera = gManager.newCamera(name);

		camera.Aspect(windowSizeX / windowSizeY);
		camera.Position(CAGLM::Vec3<float>(list["position"][0], list["position"][1], list["position"][2]));
		camera.LookAt(CAGLM::Vec3<float>(list["lookat"][0], list["lookat"][1], list["lookat"][2]));
		camera.Far(list["far"]);
	}

	/** make object */
	for (auto it = save["o"].begin(); it != save["o"].end(); it++)
	{
		std::string name = it.key();
		Json list = it.value();

		auto& object = gManager.newObject(name);
		auto model = gManager.newModel(list["fileName"]);

		object.bind(model);
		object.Size(list["size"]);
		object.Position(CAGLM::Vec3<float>(list["position"][0], list["position"][1], list["position"][2]));
	}

	/** make Light */
	gManager.iWannaLight();

	gManager.getLight()->Position(CAGLM::Vec3<float>(40, 200, -50));
	
	gManager.refresh();

	in.close();
}

/**** print string ****/
void printF(int progress)
{
	switch (progress)
	{
	case printCamera:
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "\r#Camera tracing: X=" << gManager.getCamera("camera1")->X() << " Y=" << gManager.getCamera("camera1")->Y() << " Z=" << gManager.getCamera("camera1")->Z()
			<< " roll=" << gManager.getCamera("camera1")->Roll() << " yaw=" << gManager.getCamera("camera1")->Yaw() << " pitch=" << gManager.getCamera("camera1")->Pitch()
			<< " fov=" << gManager.getCamera("camera1")->Fovy()<<" aspect=" << gManager.getCamera("camera1")->Aspect();
		break;
	case printLight:
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "\r#Light tracing: Y=" << gManager.getLight()->Y() << " Z=" << gManager.getLight()->Z() <<"\t\t\t\t\t\t\t\t\t";
		break;
	case printRemote:
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "\r#Remote tracing: X=" << gManager.getObject("rover")->X() << " Z=" << gManager.getObject("rover")->Z() << "\t\t\t\t\t\t\t\t\t";
		break;
	}
}

