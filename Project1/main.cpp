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


// lab 5
#include "Light.h"
#include "PhongMaterial.h"
#include "Simulation.h"
#include "Display.h"


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

// ������� ��������� ������� ������
void keyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", key);
	
	// ��� �������� ������ ������ �������� ������ ������������
	switch (static_cast<char>(key)) {
	case 'w':
		camera.rotateUpDown(1.0);
		break;
	case 's':
		camera.rotateUpDown(-1.0);
		break;
	case 'a':
		camera.rotateLeftRight(-1.0);
		break;
	case 'd':
		camera.rotateLeftRight(1.0);
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
	glutCreateWindow("����");
	
	initData();
	light.setPosition(pos);


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