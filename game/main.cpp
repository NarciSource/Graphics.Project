#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

#include "main.hpp"
#include "json.h"

using Json = nlohmann::json;

GLint windowSizeX = 2048, windowSizeY = 1024;
int shadingType= typePhong;

CAGLE::Management m = CAGLE::Management::get_instance();

void main(int argc, char* argv[]) {

	/** glut, windows setting */
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowSizeX, windowSizeY);
	glutCreateWindow("Graphics.Project. 20113560 -Shader");

	/** gl setting => gl.cpp */
	myGLInit();

	Json save;
	std::ifstream in("data.json");
	in >> save;

	/** make Light */
	m.iWannaLight();
	m.getLight()->getObject()->dataLoad("data\\star.obj");
		
	
	/** make Camera */
	m.iWannaCamera();
	m.getCamera()->getWeaponObject()->dataLoad("data\\BOW.obj");
	m.getCamera()->getCharacterObject()->dataLoad("data\\CV Catwoman.obj");
	m.getCamera()->Aspect(windowSizeX / windowSizeY);


	/** make object */

	for (auto it = save.begin(); it != save.end(); it++)
	{
		std::string name = it.key();
		Json each = it.value();

		m.newObject(name);
		m.getObject(name)->dataLoad(each["fileName"]);
		m.getObject(name)->Size(each["size"]);
	}

	m.newObject("teapot");
	m.getObject("teapot")->dataLoad2("data\\teapot.dat");

	m.newObject("bottom");
	m.getObject("bottom")->dataLoad2("data\\board.dat");

	m.copyObject("tree", "tree", 15);

	m.copyObject("tiger", "tiger", 5);

	/** set there's position */
	setInitPosition();


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
void setInitPosition()
{

	m.getLight()->Position(CAGLM::Vec3<float>(40, 200, -50));
	m.getLight()->getObject()->Color(0xFFFF00);
	m.getLight()->getObject()->Size(0.1f);

	m.getCamera()->Position(CAGLM::Vec3<float>(0, 20, 100));
	m.getCamera()->LookAt(CAGLM::Vec3<float>(0, 50, 0));
	m.getCamera()->Far(500.f);
	m.getCamera()->getCharacterObject()->Size(0.2f);
	


	m.getObject("rover")->Position(CAGLM::Vec3<float>(-30, 0, 130));
	m.getObject("rover")->Size(5);


	m.getObject("teapot")->Position(CAGLM::Vec3<float>(-10, 0, -50));
	m.getObject("teapot")->Size(5);


	m.getObject("tree0")->Position(CAGLM::Vec3<float>(10, 0, 10));
	m.getObject("tree1")->Position(CAGLM::Vec3<float>(5, 0, -10));
	m.getObject("tree2")->Position(CAGLM::Vec3<float>(-15, 0, 5));
	m.getObject("tree3")->Position(CAGLM::Vec3<float>(20, 0, 10));
	m.getObject("tree4")->Position(CAGLM::Vec3<float>(50, 0, 50));
	m.getObject("tree5")->Position(CAGLM::Vec3<float>(200, 0, 0));
	m.getObject("tree6")->Position(CAGLM::Vec3<float>(-80, 0, 10));
	m.getObject("tree7")->Position(CAGLM::Vec3<float>(-10, 0, -100));
	m.getObject("tree8")->Position(CAGLM::Vec3<float>(90, 0, -70));
	m.getObject("tree9")->Position(CAGLM::Vec3<float>(200, 0, -40));
	m.getObject("tree10")->Position(CAGLM::Vec3<float>(-170, 0, 30));
	m.getObject("tree11")->Position(CAGLM::Vec3<float>(-200, 0, -100));
	m.getObject("tree12")->Position(CAGLM::Vec3<float>(-100, 0, 50));
	m.getObject("tree13")->Position(CAGLM::Vec3<float>(20, 0, -150));
	m.getObject("tree14")->Position(CAGLM::Vec3<float>(-400, 0, -140));



	m.getObject("tiger0")->Position(CAGLM::Vec3<float>(30, 10, 100));
	m.getObject("tiger1")->Position(CAGLM::Vec3<float>(-100, 10, 0));
	m.getObject("tiger2")->Position(CAGLM::Vec3<float>(10, 10, -20));
	m.getObject("tiger3")->Position(CAGLM::Vec3<float>(70, 10, -70));
	m.getObject("tiger4")->Position(CAGLM::Vec3<float>(0, 0, 0));



	m.getObject("bottom")->Size(500);
	m.getObject("bottom")->Position(CAGLM::Vec3<float>(0, 0, 0));
	m.getObject("bottom")->Color(0x66CC66);

	
	m.refresh();
}

/**** print string ****/
void printF(int progress)
{
	switch (progress)
	{
	case printCamera:
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "\r#Camera tracing: X=" << m.getCamera()->X() << " Y=" << m.getCamera()->Y() << " Z=" << m.getCamera()->Z()
			<< " roll=" << m.getCamera()->Roll() << " yaw=" << m.getCamera()->Yaw() << " pitch=" << m.getCamera()->Pitch()
			<< " fov=" << m.getCamera()->Fovy()<<" aspect=" << m.getCamera()->Aspect();
		break;
	case printLight:
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "\r#Light tracing: Y=" << m.getLight()->Y() << " Z=" << m.getLight()->Z() <<"\t\t\t\t\t\t\t\t\t";
		break;
	case printRemote:
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "\r#Remote tracing: X=" << m.getObject("rover")->X() << " Z=" << m.getObject("rover")->Z() << "\t\t\t\t\t\t\t\t\t";
		break;
	}
}

