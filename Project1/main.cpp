#include <windows.h>

#include <iostream>
#include <vector>

#include <cstdlib> // ��� ������� rand() � srand()

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"


//Lab 2
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
using namespace glm;

// ���������� ������������ ���� ����������� ����������
using namespace std;

//Lab 3
#include "GraphicObject.h"


// lab 4
#include "Data.h"
#include <sstream>
#include <string>

#include <chrono>

Camera camera; // �������� ������� ������

float FrameTime = 0;
int FPS = 0;

unsigned int mCurrentTick = 0;

float getSimulationTime();

// lab5

GLfloat pos[] = {0, 0, 0};

// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void display(void)
{
	FPS++;
	// �������� ����� ����� � ����� �������
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	// ������������� ������

	// ������������� ����� ������� ������������
	GLfloat globalAmbientColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);

	// �������� ������� �������� �����
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	camera.apply();

	
	// ����� ������� �������
	graphicObjects[0].draw();
	//graphicObjects[0].printModelMatrix();
	//cin.get();
	// ����� ������ �������
	graphicObjects[1].draw();
	// ����� ��������� �������
	graphicObjects[2].draw();
	// ����� ������� �������
	graphicObjects[3].draw();

	
	// ����� ��������� � ������� �������
	glutSwapBuffers();
};
// ������� ��������� - ���������� ����������� �����
// ����� ������� ����������� ���������� �������
// ��� ���� �������������� � ������� glutIdleFunc
void simulation()
{
	// ����������� ������� ���������
	float simulationTime = getSimulationTime();
	// ������������ ������
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
	FrameTime += simulationTime;
	FPS++;
	if (FrameTime >= 1) {
		std::stringstream ss;
		ss << FPS << " FPS";
		std::string fpsString = ss.str();
		cout << "FPS = " << FPS << endl; 
		glutSetWindowTitle(fpsString.c_str());
		FPS = 0;
		FrameTime = 0;
	}
};


// ������� ��������� ������� ������
void keyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", key);
	
	// ��� �������� ������ ������ �������� ������ ������������
	switch (static_cast<char>(key)) {
	case 'w':
		camera.rotateUpDown(5.0);
		break;
	case 's':
		camera.rotateUpDown(-5.0);
		break;
	case 'a':
		camera.rotateLeftRight(-5.0);
		break;
	case 'd':
		camera.rotateLeftRight(5.0);
		break;
	case '+':
		camera.zoomInOut(0.2);
		break;
	case '-':
		camera.zoomInOut(-0.2);
		break;
	}
	
};



void main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");

	// ������������� ���������� GLUT
	glutInit(&argc, argv);
	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// �������� ����:
	// 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 200);
	// 2. ������������� ������ ����
	glutInitWindowSize(800, 600);
	// 3. ������� ����
	glutCreateWindow("������");
	GraphicObject GraphicObject1;
	GraphicObject1.setPosition(vec3(4, 0, 0));
	GraphicObject1.setAngle(180);
	GraphicObject1.set�olor(vec3(1, 0, 0));
	graphicObjects.push_back(GraphicObject1);

	GraphicObject GraphicObject2;
	GraphicObject2.setPosition(vec3(-4, 0, 0));
	GraphicObject2.setAngle(0);
	GraphicObject2.set�olor(vec3(0, 0, 1));
	graphicObjects.push_back(GraphicObject2);

	GraphicObject GraphicObject3;
	GraphicObject3.setPosition(vec3(0, 0, 4));
	GraphicObject3.setAngle(90);
	GraphicObject3.set�olor(vec3(1, 1, 1));
	graphicObjects.push_back(GraphicObject3);

	GraphicObject GraphicObject4;
	GraphicObject4.setPosition(vec3(0, 0, -4));
	GraphicObject4.setAngle(270);
	GraphicObject4.set�olor(vec3(0, 1, 0));
	graphicObjects.push_back(GraphicObject4);


	// �������� ����� ������� ���������
	glEnable(GL_LIGHTING);



	// ��������� ������� ��������� ������
	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(reshape);
	// ������������� �������, ������� ����� ������� ��� ����� �������
	glutIdleFunc(simulation);
	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	glutKeyboardFunc(keyboardFunc);

	// ������������� ������, ����������� ��� ������ ���������:
// ������������� ����������� ��������


	// �������� ���� ��������� ��������� ��
	glutMainLoop();

};