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
	for(auto each: m.get_all_objects())
	{	
		auto obj1 = each.second;
		if (obj1->herNameIs().find("arrow", 0, 5) == std::string::npos) continue;
		std::string name = obj1->herNameIs();
		std::cout << name;
		bool flagCollison=false;

		/* If arrow is too far from the camera, erase it out. */
		if ((m.getObject(name)->Position() - m.getCamera()->Position()).length() >100) {
			m.deleteObject(name);
			continue;
		}


		for(auto each2: m.get_all_objects())
		{
			auto obj = each2.second;
			/* There is no effect between arrows */
			if (obj->herNameIs().find("arrow", 0, 5) != std::string::npos) continue;

			if (m.isCollision(name, obj->herNameIs()))
			{
				flagCollison = true;
				break;
			}
		}
		/* Arrow does not collision anything */
		if (!flagCollison)
		{
			m.getObject(name)->forward(sensitivity);
		}		
	}


	/** Tiger action **/
	for (int numoftigers = 0; numoftigers < 5; numoftigers++)
	{
		std::string name = "tiger" + std::to_string(numoftigers);

		if (m.getObject(name) == nullptr) continue;

		if (name == "tiger0")
		{
			m.getObject(name)->forward(sensitivity*1.f);
			m.getObject(name)->around(sensitivity*1.f);
		}
		if (name == "tiger1")
		{
			m.getObject(name)->forward(sensitivity*0.2f);
		}
		if (name == "tiger3")
		{
			m.getObject(name)->forward(sensitivity*5.f);
			m.getObject(name)->around(-sensitivity*2.f);
		}
		for(auto each: m.get_all_objects())
		{
			auto obj = each.second;
			if (obj->herNameIs().find("arrow", 0, 5) != std::string::npos)
			{
				if (m.isCollision(name, obj->herNameIs(),20))
				{
					m.deleteObject(name);
					break;
				}
			}
			if (obj->hisNameIs() == "rover")
			{
				if (m.isCollision(name, obj->hisNameIs(),40))
				{
					m.deleteObject(name);
					break;
				}
			}
		}
	}


	/** Camera jump action effected on gravity */
	if (m.getCamera()->Position().Y() > 10) //gravity
	{
		m.getCamera()->move(CAGLE_DOWN, 0.03);
	}


	/** Light auto sunset effect */
	if (flagTimeFast)
	{
		m.getLight()->Pitch(
			m.getLight()->Pitch() + sensitivity*0.05f
		);
		m.getLight()->sunset(sensitivity);
		m.getLight()->refresh();
		printF(printLight);
	}

 	glutPostRedisplay();
	glutTimerFunc(sensitivityFrame, idle, 1);
}
/**** Handler: MouseClick ****/
void mouseClickHandler(const int button, const int state, const int x, const int y)
{
	static int beforeFovy = m.getCamera()->Fovy();

	/* When you hold down right mouse button,
	* show it at sniper style */
	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) m.getCamera()->Fovy(0.2);
	else {
		m.getCamera()->Fovy(beforeFovy);
		beforeFovy = m.getCamera()->Fovy();
	}

	/* When you click left button,
	* make an arrow on the spot.*/
	if (button == GLUT_LEFT_BUTTON) mkarrow();

	m.getCamera()->shutter();
}
/**** Handler: Mouse moving ****/
void mouseMoveHandler(const int x, const int y)
{
	static int beforeX, beforeY;

	if (x - beforeX < 0)
		m.getCamera()->lookAround(CAGLE_LEFT, -(x - beforeX)* sensitivity*0.03);
	if (x - beforeX > 0)
		m.getCamera()->lookAround(CAGLE_RIGHT, (x - beforeX)* sensitivity*0.03);
	if (y - beforeY < 0)
		m.getCamera()->lookAround(CAGLE_UP, -(y - beforeY)* sensitivity *1.5);
	if (y - beforeY > 0)
		m.getCamera()->lookAround(CAGLE_DOWN, (y - beforeY)* sensitivity *1.5);

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
		m.getCamera()->move(CAGLE_FORWARD, sensitivity); break;
	case 'W':
		m.getCamera()->move(CAGLE_FORWARD, sensitivity * 3); break;
	case 's':
		m.getCamera()->move(CAGLE_BACKWARD, sensitivity); break;
	case 'S':
		m.getCamera()->move(CAGLE_BACKWARD, sensitivity * 3); break;
	case 'a':
		m.getCamera()->move(CAGLE_LEFT, sensitivity); break;
	case 'A':
		m.getCamera()->move(CAGLE_LEFT, sensitivity * 3); break;
	case 'd':
		m.getCamera()->move(CAGLE_RIGHT, sensitivity); break;
	case 'D':
		m.getCamera()->move(CAGLE_RIGHT, sensitivity * 3); break;


		/** Shader type changing */
	case 'g':
		shadingType = typeGouraud;	break;
	case 'h':
		shadingType = typePhong;	break;


		/** Romote rover object */
	case '8':
		flagRoverRemoteControl = true;
		m.getObject("rover")->forward(sensitivity*0.4f);
		printF(printRemote); break;
	case '2':
		flagRoverRemoteControl = true;
		m.getObject("rover")->forward(-sensitivity*0.4f);
		printF(printRemote); break;
	case '4':
		m.getObject("rover")->around(-sensitivity*2.f );
		m.getObject("rover")->forward(sensitivity*0.4f);
		printF(printRemote); break;
	case '6':
		m.getObject("rover")->around( sensitivity*2.f);
		m.getObject("rover")->forward(sensitivity*0.4f);
		printF(printRemote); break;


		/** Fovy changing */
	case ',':
		m.getCamera()->fovyDown(10); break;
	case '.':
		m.getCamera()->fovyUp(10); break;

	case 'p':
		m.getCamera()->projectionSwitch(PROJECTION_PERSPECTIVE);	break;
	case 'o':
		m.getCamera()->projectionSwitch(PROJECTION_ORTHOGONAL);		break;
	case 'm':
		m.getCamera()->projectionSwitch(PROJECTION_MAPVIEW);		break;


		/** Shid down/up */
	case 'z':
		if (flagShit) m.getCamera()->move(CAGLE_DOWN, sensitivity);
		else m.getCamera()->move(CAGLE_UP, sensitivity);
		flagShit = !flagShit;
		break;
		/** Jump */
	case 32: // space bar = Jump
		m.getCamera()->move(CAGLE_UP, sensitivity * 3);
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
		m.getLight()->Position(
			m.getLight()->Position() + CAGLM::Vec3<float>(0, 0, -sensitivity*10)
		);
		break;
	case GLUT_KEY_DOWN:
		m.getLight()->Position(
			m.getLight()->Position() + CAGLM::Vec3<float>(0, 0, sensitivity*10)
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
	m.getLight()->refresh();
}
/**** Handler: Extend screen size ****/
void changeSize(int width, int height)
{
	glViewport(0, 0, width, height);

	m.getCamera()->Aspect(1.0f*width / height);
}








/**** Dynamic creation of arrows ****/
void mkarrow()
{
/*	auto arrow = m.iWannaObject("arrow");
	/* Set of Arrow
	* to position and direction of Bow */
/*	arrow->Position(
		m.getCamera()->getWeaponObject()->Position() + CAGLM::Vec3<float>(0, -2, -5)
	);
	arrow->Yaw(
		m.getCamera()->getWeaponObject()->Yaw()
	);
	arrow->Size(5);
*/
	m.refresh();
}