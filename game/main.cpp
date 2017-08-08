#include <iostream>
#include <string>
#include <Windows.h>

#include "main.hpp"




GLint windowSizeX = 2048, windowSizeY = 1024;
int shadingType= typePhong;



void mkObject(std::string _name, int _num)
{
	std::string name;
	if(_num>=10) name = _name + (char)(_num / 10 + '0') + (char)(_num%10 + '0');
	else name = _name + (char)(_num + '0');

	manager.iWannaObject("intern_" + _name)->herNameIs(name);
}
void main(int argc, char* argv[]) {

	/** glut, windows setting */
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowSizeX, windowSizeY);
	glutCreateWindow("Graphics.Project. 20113560 -Shader");

	/** gl setting => gl.cpp */
	myGLInit();




	/** make Light */
	manager.iWannaLight();
	manager.getLight()->getObject()->dataLoad("data\\star.obj");
		
	
	/** make Camera */
	manager.iWannaCamera();
	manager.getCamera()->getWeaponObject()->dataLoad("data\\BOW.obj");
	manager.getCamera()->getCharacterObject()->dataLoad("data\\CV Catwoman.obj");
	manager.getCamera()->Aspect(windowSizeX / windowSizeY);


	/** make object */
	manager.iWannaObject()->herNameIs("rover");
	manager.getObject("rover")->dataLoad("data\\Mars Rock Collecter.obj");

	manager.iWannaObject()->hisNameIs("teapot");
	manager.getObject("teapot")->dataLoad2("data\\teapot.dat");

	manager.iWannaObject()->herNameIs("bottom");
	manager.getObject("bottom")->dataLoad2("data\\board.dat");
	

	manager.iWannaInternObject()->hisNameIs("intern_tree");
	manager.getInternObject("intern_tree")->dataLoad("data\\PineTree.obj");
	manager.getInternObject("intern_tree")->Size(50);
	for (int i = 0; i < 15; i++) mkObject("tree",i);


	manager.iWannaInternObject()->herNameIs("internArrow");
	manager.getInternObject("internArrow")->dataLoad("data\\Arrow.obj");



	manager.iWannaInternObject()->hisNameIs("intern_tiger");
	manager.getInternObject("intern_tiger")->dataLoad3("data\\tigre_sumatra_sketchfab.obj");
	manager.getInternObject("intern_tiger")->Size(30);
	for (int i = 0; i < 5; i++) mkObject("tiger", i);


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

	manager.getLight()->Position(CAGLM::Vec3(40, 200, -50));
	manager.getLight()->getObject()->Color(0xFFFF00);
	manager.getLight()->getObject()->Size(0.1f);

	manager.getCamera()->Position(CAGLM::Vec3(0, 20, 100));
	manager.getCamera()->LookAt(CAGLM::Vec3(0, 50, 0));
	manager.getCamera()->Far(500.f);
	manager.getCamera()->getCharacterObject()->Size(0.2f);
	


	manager.getObject("rover")->Position(CAGLM::Vec3(-30, 0, 130));
	manager.getObject("rover")->Size(5);


	manager.getObject("teapot")->Position(CAGLM::Vec3(-10, 0, -50));
	manager.getObject("teapot")->Size(5);


	manager.getObject("tree0")->Position(CAGLM::Vec3(10, 0, 10));
	manager.getObject("tree1")->Position(CAGLM::Vec3(5, 0, -10));
	manager.getObject("tree2")->Position(CAGLM::Vec3(-15, 0, 5));
	manager.getObject("tree3")->Position(CAGLM::Vec3(20, 0, 10));
	manager.getObject("tree4")->Position(CAGLM::Vec3(50, 0, 50));
	manager.getObject("tree5")->Position(CAGLM::Vec3(200, 0, 0));
	manager.getObject("tree6")->Position(CAGLM::Vec3(-80, 0, 10));
	manager.getObject("tree7")->Position(CAGLM::Vec3(-10, 0, -100));
	manager.getObject("tree8")->Position(CAGLM::Vec3(90, 0, -70));
	manager.getObject("tree9")->Position(CAGLM::Vec3(200, 0, -40));
	manager.getObject("tree10")->Position(CAGLM::Vec3(-170, 0, 30));
	manager.getObject("tree11")->Position(CAGLM::Vec3(-200, 0, -100));
	manager.getObject("tree12")->Position(CAGLM::Vec3(-100, 0, 50));
	manager.getObject("tree13")->Position(CAGLM::Vec3(20, 0, -150));
	manager.getObject("tree14")->Position(CAGLM::Vec3(-400, 0, -140));



	manager.getObject("tiger0")->Position(CAGLM::Vec3(30, 10, 100));
	manager.getObject("tiger1")->Position(CAGLM::Vec3(-100, 10, 0));
	manager.getObject("tiger2")->Position(CAGLM::Vec3(10, 10, -20));
	manager.getObject("tiger3")->Position(CAGLM::Vec3(70, 10, -70));
	manager.getObject("tiger4")->Position(CAGLM::Vec3(0, 0, 0));



	manager.getObject("bottom")->Size(500);
	manager.getObject("bottom")->Position(CAGLM::Vec3(0, 0, 0));
	manager.getObject("bottom")->Color(0x66CC66);

	
	manager.refresh();
}

/**** print string ****/
void printF(int progress)
{
	switch (progress)
	{
	case printCamera:
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "\r#Camera tracing: X=" << manager.getCamera()->X() << " Y=" << manager.getCamera()->Y() << " Z=" << manager.getCamera()->Z()
			<< " roll=" << manager.getCamera()->Roll() << " yaw=" << manager.getCamera()->Yaw() << " pitch=" << manager.getCamera()->Pitch()
			<< " fov=" << manager.getCamera()->Fovy()<<" aspect=" << manager.getCamera()->Aspect();
		break;
	case printLight:
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "\r#Light tracing: Y=" << manager.getLight()->Y() << " Z=" << manager.getLight()->Z() <<"\t\t\t\t\t\t\t\t\t";
		break;
	case printRemote:
		std::cout << std::fixed;
		std::cout.precision(1);
		std::cout << "\r#Remote tracing: X=" << manager.getObject("rover")->X() << " Z=" << manager.getObject("rover")->Z() << "\t\t\t\t\t\t\t\t\t";
		break;
	}
}

