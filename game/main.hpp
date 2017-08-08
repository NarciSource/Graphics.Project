#pragma once

#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"cagle.lib")


#include "glew.h"
#include "glut.h"

#include "shader.hpp"
#include "cagle.h"
#include "caglemannager.h"

#define typeGouraud 0x01
#define typePhong 0x02
#define printCamera 0x0003
#define printLight 0x0004
#define printRemote 0x0005


extern GLint windowSizeX, windowSizeY;
extern CAGLE::Management manager;

extern int shadingType;


/** init.cpp */
void myGLInit();
void renderObject(CAGLE::Object *_model);
void render();

/** main.cpp */
void keyboardHandler(const unsigned char key, const int x, const int y);
void mouseMoveHandler(const int x, const int y);
void mouseClickHandler(const int button, const int state, const int x, const int y);
void specialKeyboardHandler(const int key, const int x, const int y);
void idle(int _value);
void setInitPosition();
void printF(const int progress);
void changeSize(const int _width, const int _height);
