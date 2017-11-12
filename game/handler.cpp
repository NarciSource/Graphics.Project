#include "main.hpp"
#include <iostream>

bool flagRoverRemoteControl = false;
bool flagTimeFast = false;
float sensitivity = 1.f;
float sensitivityFrame = 30;

void mkarrow();
/**** no action, runtime ****/
void idle(int value)
{

	/** Arrow action */
	for (auto obj1: manager.getAllobjects())
	{
		if (obj1->herNameIs().find("arrow", 0, 5) == std::string::npos) continue;
		std::string name = obj1->herNameIs();
		std::cout << name;
		bool flagCollison=false;

		/* If arrow is too far from the camera, erase it out. */
		if ((manager.getObject(name)->Position() - manager.getCamera()->Position()).length() >100) {
			manager.fireObject(name);
			continue;
		}


		for (auto obj : manager.getAllobjects())
		{
			/* There is no effect between arrows */
			if (obj->herNameIs().find("arrow", 0, 5) != std::string::npos) continue;

			if (manager.isCollision(name, obj->herNameIs()))
			{
				flagCollison = true;
				break;
			}
		}
		/* Arrow does not collision anything */
		if (!flagCollison)
		{
			manager.getObject(name)->forward(sensitivity);
		}		
	}


	/** Tiger action **/
	for (int numoftigers = 0; numoftigers < 5; numoftigers++)
	{
		std::string name = "tiger" + std::to_string(numoftigers);

		if (manager.getObject(name) == nullptr) continue;

		if (name == "tiger0")
		{
			manager.getObject(name)->forward(sensitivity*1.f);
			manager.getObject(name)->around(sensitivity*1.f);
		}
		if (name == "tiger1")
		{
			manager.getObject(name)->forward(sensitivity*0.2f);
		}
		if (name == "tiger3")
		{
			manager.getObject(name)->forward(sensitivity*5.f);
			manager.getObject(name)->around(-sensitivity*2.f);
		}
		for (auto obj : manager.getAllobjects())
		{
			if (obj->herNameIs().find("arrow", 0, 5) != std::string::npos)
			{
				if (manager.isCollision(name, obj->herNameIs(),20))
				{
					manager.fireObject(name);
					break;
				}
			}
			if (obj->hisNameIs() == "rover")
			{
				if (manager.isCollision(name, obj->hisNameIs(),40))
				{
					manager.fireObject(name);
					break;
				}
			}
		}
	}


	/** Camera jump action effected on gravity */
	if (manager.getCamera()->Position().Y() > 10) //gravity
	{
		manager.getCamera()->move(CAGLE_DOWN, 0.03);
	}


	/** Light auto sunset effect */
	if (flagTimeFast)
	{
		manager.getLight()->Pitch(
			manager.getLight()->Pitch() + sensitivity*0.05f
		);
		manager.getLight()->sunset(sensitivity);
		manager.getLight()->refresh();
		printF(printLight);
	}

 	glutPostRedisplay();
	glutTimerFunc(sensitivityFrame, idle, 1);
}
/**** Handler: MouseClick ****/
void mouseClickHandler(const int button, const int state, const int x, const int y)
{
	static int beforeFovy = manager.getCamera()->Fovy();

	/* When you hold down right mouse button,
	* show it at sniper style */
	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) manager.getCamera()->Fovy(0.2);
	else {
		manager.getCamera()->Fovy(beforeFovy);
		beforeFovy = manager.getCamera()->Fovy();
	}

	/* When you click left button,
	* make an arrow on the spot.*/
	if (button == GLUT_LEFT_BUTTON) mkarrow();

	manager.getCamera()->shutter();
}
/**** Handler: Mouse moving ****/
void mouseMoveHandler(const int x, const int y)
{
	static int beforeX, beforeY;

	if (x - beforeX < 0)
		manager.getCamera()->lookAround(CAGLE_LEFT, -(x - beforeX)* sensitivity*0.03);
	if (x - beforeX > 0)
		manager.getCamera()->lookAround(CAGLE_RIGHT, (x - beforeX)* sensitivity*0.03);
	if (y - beforeY < 0)
		manager.getCamera()->lookAround(CAGLE_UP, -(y - beforeY)* sensitivity *1.5);
	if (y - beforeY > 0)
		manager.getCamera()->lookAround(CAGLE_DOWN, (y - beforeY)* sensitivity *1.5);

	beforeX = x;	beforeY = y;
	printF(printCamera);
}
/**** Handler: Keyboard typing ****/
void keyboardHandler(const unsigned char key, const int x, const int y)
{
	static bool flagShit = true;

	switch (key)
	{
		/** Character Moving */
	case 'w':
		manager.getCamera()->move(CAGLE_FORWARD, sensitivity); break;
	case 'W':
		manager.getCamera()->move(CAGLE_FORWARD, sensitivity * 3); break;
	case 's':
		manager.getCamera()->move(CAGLE_BACKWARD, sensitivity); break;
	case 'S':
		manager.getCamera()->move(CAGLE_BACKWARD, sensitivity * 3); break;
	case 'a':
		manager.getCamera()->move(CAGLE_LEFT, sensitivity); break;
	case 'A':
		manager.getCamera()->move(CAGLE_LEFT, sensitivity * 3); break;
	case 'd':
		manager.getCamera()->move(CAGLE_RIGHT, sensitivity); break;
	case 'D':
		manager.getCamera()->move(CAGLE_RIGHT, sensitivity * 3); break;


		/** Shader type changing */
	case 'g':
		shadingType = typeGouraud;	break;
	case 'h':
		shadingType = typePhong;	break;


		/** Romote rover object */
	case '8':
		flagRoverRemoteControl = true;
		manager.getObject("rover")->forward(sensitivity*0.4f);
		printF(printRemote); break;
	case '2':
		flagRoverRemoteControl = true;
		manager.getObject("rover")->forward(-sensitivity*0.4f);
		printF(printRemote); break;
	case '4':
		manager.getObject("rover")->around(-sensitivity*2.f );
		manager.getObject("rover")->forward(sensitivity*0.4f);
		printF(printRemote); break;
	case '6':
		manager.getObject("rover")->around( sensitivity*2.f);
		manager.getObject("rover")->forward(sensitivity*0.4f);
		printF(printRemote); break;


		/** Fovy changing */
	case ',':
		manager.getCamera()->fovyDown(10); break;
	case '.':
		manager.getCamera()->fovyUp(10); break;

	case 'p':
		manager.getCamera()->projectionSwitch(PROJECTION_PERSPECTIVE);	break;
	case 'o':
		manager.getCamera()->projectionSwitch(PROJECTION_ORTHOGONAL);		break;
	case 'm':
		manager.getCamera()->projectionSwitch(PROJECTION_MAPVIEW);		break;


		/** Shid down/up */
	case 'z':
		if (flagShit) manager.getCamera()->move(CAGLE_DOWN, sensitivity);
		else manager.getCamera()->move(CAGLE_UP, sensitivity);
		flagShit = !flagShit;
		break;
		/** Jump */
	case 32: // space bar = Jump
		manager.getCamera()->move(CAGLE_UP, sensitivity * 3);
		break;
		
	case 13:
		glutFullScreen();
			break;
		/** Auto sunset */
	case 't':
		flagTimeFast = !flagTimeFast;
		break;
		/** ESC */
	case 27:
		exit(0);
	}

	glutPostRedisplay();
}
/**** Handler: Special Keyboard ****/
void specialKeyboardHandler(const int key, const int x, const int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		manager.getLight()->Position(
			manager.getLight()->Position() + CAGLM::Vec3<float>(0, 0, -sensitivity*10)
		);
		break;
	case GLUT_KEY_DOWN:
		manager.getLight()->Position(
			manager.getLight()->Position() + CAGLM::Vec3<float>(0, 0, sensitivity*10)
		);
		break;
	case GLUT_KEY_PAGE_UP:
		if(sensitivity > 1) sensitivity++;
		else sensitivity *= 1.1f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (sensitivity > 1) sensitivity--;
		else sensitivity *= 0.9f;
		break;
	case GLUT_KEY_HOME:
		sensitivityFrame--;
		break;
	case GLUT_KEY_END:
		sensitivityFrame++;
		break;
	}
	manager.getLight()->refresh();
}
/**** Handler: Extend screen size ****/
void changeSize(int width, int height)
{
	glViewport(0, 0, width, height);

	manager.getCharacter()->getEye()->Aspect(1.0f*width / height);
}








/**** Dynamic creation of arrows ****/
void mkarrow()
{
	auto arrow = manager.iWannaObject("arrow");
	/* Set of Arrow
	* to position and direction of Bow */
	arrow->Position(
		manager.getCharacter()->Position() + CAGLM::Vec3<float>(0, -2, -5)
	);
	arrow->Yaw(
		manager.getCamera()->getWeaponObject()->Yaw()
	);
	arrow->Size(5);

	manager.refresh();
}