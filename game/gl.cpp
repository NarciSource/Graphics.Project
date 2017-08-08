#include <iostream>

#include "main.hpp"
#include "cagle.h"


CAGLE::Management manager;
GLuint ProgramID;
GLint modelMatrixID, viewMatrixID, projectionMatrixID;
GLint vertexPositionID,  normalID;
GLint colorID, lightID, cameraID;
GLint shadingTypeID;
GLuint texture;


void myGLInit()
{
	glEnable(GL_DEPTH_TEST);
	int glewtest = glewInit();
	if (glewtest != GLEW_OK) {
		std::cout<<"glew error"<<std::endl;
	}

	ProgramID = shader::LoadShaders("shader\\VertexShader.vert", "shader\\FragmentShader.frag");

	modelMatrixID = glGetUniformLocation(ProgramID, "modelMatrix");
	viewMatrixID = glGetUniformLocation(ProgramID, "viewMatrix");
	projectionMatrixID = glGetUniformLocation(ProgramID, "projectionMatrix");

	vertexPositionID = glGetAttribLocation(ProgramID, "vertexPosition");
	normalID = glGetAttribLocation(ProgramID, "vertexNormal");

	colorID = glGetUniformLocation(ProgramID, "colorValue");
	lightID = glGetUniformLocation(ProgramID, "lightPosition");
	cameraID = glGetUniformLocation(ProgramID, "cameraPosition");

	shadingTypeID = glGetUniformLocation(ProgramID, "shadingType");

	/*
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //<7>
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //<8>

	glTexImage2D(GL_TEXTURE_2D, 0, 3, texRec[i]->sizeX, texRec[i]->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texRec[i]->data); //<9>	//이미지 데이터

	texRec[i]->해제해도 됨.




	glEnable(GL_TEXTURE_2D);
	*/










	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

	/*
	GLfloat fogColor[4] = {0.5f,0.5f,1.0f,1.0f};
	glFogi(GL_FOG_MODE, GL_LINEAR);     //
	glFogfv(GL_FOG_COLOR, fogColor);    // LINEAR모드의 안개 색 지정
	glFogf(GL_FOG_DENSITY, 0.3f);       // 안개의 밀도 지정.GL_EXP,GL_EXP2만 사용 
	glHint(GL_FOG_HINT, GL_NICEST);     // 멋있게 해달라구 요구
	glFogf(GL_FOG_START, 5.5f);         // LINEAR에서만 적용 안개가 보이는 Z값
	glFogf(GL_FOG_END, 7.0f);           // 안개가 들이워져서 물체가 보이지 않는 Z값
	glEnable(GL_FOG);                   // 안개 사용
	*/
}
void renderObject(CAGLE::Object *_object)
{

	/** Model Matrix */
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, _object->loadModelMatrix());

	/** Color */
	glUniform4f(colorID, 1.f* (_object->Color() / 0x10000) / 0xFF,
		1.f* (_object->Color() / 0x100 % 0x100) / 0xFF,
		1.f* (_object->Color() % 0x100) / 0xFF,
		0.0f
	);


	/** Vertex */
	glVertexAttribPointer(
		vertexPositionID,// The attribute we want to configure
		3,    // size
		GL_FLOAT,// type
		GL_FALSE,// normalized?
		sizeof(GLfloat) * 3,// stride
		_object->loadVertexPosition()// array buffer offset
	);


	/** Normal Vector */
	glVertexAttribPointer(
		normalID,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(GLfloat) * 3,
		_object->loadNormal()
	);




	/** Draw call */
	glDrawArrays(GL_TRIANGLES, 0, _object->loadPolygonCount() * 3);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	/****** Shader Program Bind Start ******/
	glUseProgram(ProgramID);


	
	/** View and Projection Matrix */
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, manager.getCamera()->loadViewMatrix());
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, manager.getCamera()->loadProjectionMatrix());

	/** Camera and Light position */
	glUniform4f(cameraID, manager.getCamera()->X(), manager.getCamera()->Y(), manager.getCamera()->Z(), 0);
	glUniform4f(lightID, manager.getLight()->X(), manager.getLight()->Y(), manager.getLight()->Z(), 0);

	/** Shading Type, I supported phong and gouroud */
	glUniform1i(shadingTypeID, shadingType);
	

	glEnableVertexAttribArray(vertexPositionID);
	glEnableVertexAttribArray(normalID);
	

	/* Light object */
	renderObject(manager.getLight()->getObject());

	/* Camera object */
	renderObject(manager.getCamera()->getWeaponObject());
	renderObject(manager.getCamera()->getCharacterObject());
	/* Each object*/
	for (auto object : manager.getAllobjects())
	{
		renderObject(object);
	}





	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(normalID);








	glUseProgram(0);
	/****** Shader Program Bind End *****/

	glutSwapBuffers();
}