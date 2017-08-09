#include <iostream>
#include <string>
#include <Windows.h>

#include "main.hpp"




GLint windowSizeX = 2048, windowSizeY = 1024;
int shadingType= typePhong;



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
	

	manager.iWannaInternObject()->hisNameIs("tree");
	manager.getInternObject("tree")->dataLoad("data\\PineTree.obj");
	manager.getInternObject("tree")->Size(50);
	manager.iWannaObject("tree", 15);


	manager.iWannaInternObject()->herNameIs("arrow");
	manager.getInternObject("arrow")->dataLoad("data\\Arrow.obj");



	manager.iWannaInternObject()->hisNameIs("tiger");
	manager.getInternObject("tiger")->dataLoad("data\\tigre_sumatra_sketchfab.obj");
	manager.getInternObject("tiger")->Size(30);
	manager.iWannaObject("tiger", 5);


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

	manager.getLight()->Position(CAGLM::Vec3<float>(40, 200, -50));
	manager.getLight()->getObject()->Color(0xFFFF00);
	manager.getLight()->getObject()->Size(0.1f);

	manager.getCamera()->Position(CAGLM::Vec3<float>(0, 20, 100));
	manager.getCamera()->LookAt(CAGLM::Vec3<float>(0, 50, 0));
	manager.getCamera()->Far(500.f);
	manager.getCamera()->getCharacterObject()->Size(0.2f);
	


	manager.getObject("rover")->Position(CAGLM::Vec3<float>(-30, 0, 130));
	manager.getObject("rover")->Size(5);


	manager.getObject("teapot")->Position(CAGLM::Vec3<float>(-10, 0, -50));
	manager.getObject("teapot")->Size(5);


	manager.getObject("tree0")->Position(CAGLM::Vec3<float>(10, 0, 10));
	manager.getObject("tree1")->Position(CAGLM::Vec3<float>(5, 0, -10));
	manager.getObject("tree2")->Position(CAGLM::Vec3<float>(-15, 0, 5));
	manager.getObject("tree3")->Position(CAGLM::Vec3<float>(20, 0, 10));
	manager.getObject("tree4")->Position(CAGLM::Vec3<float>(50, 0, 50));
	manager.getObject("tree5")->Position(CAGLM::Vec3<float>(200, 0, 0));
	manager.getObject("tree6")->Position(CAGLM::Vec3<float>(-80, 0, 10));
	manager.getObject("tree7")->Position(CAGLM::Vec3<float>(-10, 0, -100));
	manager.getObject("tree8")->Position(CAGLM::Vec3<float>(90, 0, -70));
	manager.getObject("tree9")->Position(CAGLM::Vec3<float>(200, 0, -40));
	manager.getObject("tree10")->Position(CAGLM::Vec3<float>(-170, 0, 30));
	manager.getObject("tree11")->Position(CAGLM::Vec3<float>(-200, 0, -100));
	manager.getObject("tree12")->Position(CAGLM::Vec3<float>(-100, 0, 50));
	manager.getObject("tree13")->Position(CAGLM::Vec3<float>(20, 0, -150));
	manager.getObject("tree14")->Position(CAGLM::Vec3<float>(-400, 0, -140));



	manager.getObject("tiger0")->Position(CAGLM::Vec3<float>(30, 10, 100));
	manager.getObject("tiger1")->Position(CAGLM::Vec3<float>(-100, 10, 0));
	manager.getObject("tiger2")->Position(CAGLM::Vec3<float>(10, 10, -20));
	manager.getObject("tiger3")->Position(CAGLM::Vec3<float>(70, 10, -70));
	manager.getObject("tiger4")->Position(CAGLM::Vec3<float>(0, 0, 0));



	manager.getObject("bottom")->Size(500);
	manager.getObject("bottom")->Position(CAGLM::Vec3<float>(0, 0, 0));
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

