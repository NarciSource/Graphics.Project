#include <iostream>

#include "main.hpp"
#include "caglemannager.h"


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
		std::cerr<<"glew error"<<std::endl;
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

	//����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //<7>
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //<8>

	glTexImage2D(GL_TEXTURE_2D, 0, 3, texRec[i]->sizeX, texRec[i]->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texRec[i]->data); //<9>	//�̹��� ������

	texRec[i]->�����ص� ��.




	glEnable(GL_TEXTURE_2D);
	*/










	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

	/*
	GLfloat fogColor[4] = {0.5f,0.5f,1.0f,1.0f};
	glFogi(GL_FOG_MODE, GL_LINEAR);     //
	glFogfv(GL_FOG_COLOR, fogColor);    // LINEAR����� �Ȱ� �� ����
	glFogf(GL_FOG_DENSITY, 0.3f);       // �Ȱ��� �е� ����.GL_EXP,GL_EXP2�� ��� 
	glHint(GL_FOG_HINT, GL_NICEST);     // ���ְ� �ش޶� �䱸
	glFogf(GL_FOG_START, 5.5f);         // LINEAR������ ���� �Ȱ��� ���̴� Z��
	glFogf(GL_FOG_END, 7.0f);           // �Ȱ��� ���̿����� ��ü�� ������ �ʴ� Z��
	glEnable(GL_FOG);                   // �Ȱ� ���
	*/
}
void renderObject(CAGLE::Object *object)
{

	/** Model Matrix */
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, object->loadModelMatrix());

	/** Color */
	glUniform4f(colorID, 1.f* (object->Color() / 0x10000) / 0xFF,
		1.f* (object->Color() / 0x100 % 0x100) / 0xFF,
		1.f* (object->Color() % 0x100) / 0xFF,
		0.0f
	);


	/** Vertex */
	glVertexAttribPointer(
		vertexPositionID,// The attribute we want to configure
		3,    // size
		GL_FLOAT,// type
		GL_FALSE,// normalized?
		sizeof(GLfloat) * 3,// stride
		object->loadVertexPosition()// array buffer offset
	);


	/** Normal Vector */
	glVertexAttribPointer(
		normalID,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(GLfloat) * 3,
		object->loadNormal()
	);




	/** Draw call */
	glDrawArrays(GL_TRIANGLES, 0, object->loadPolygonCount() * 3);
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