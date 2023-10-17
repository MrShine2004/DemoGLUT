#include <windows.h>

#include <iostream>
#include <vector>

#include <cstdlib> // Для функций rand() и srand()

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

// используем пространство имен стандартной библиотеки
using namespace std;

//Lab 3
#include "GraphicObject.h"


// lab 4
#include "Data.h"
#include <sstream>
#include <string>

#include <chrono>

Camera camera; // Создание объекта камеры

float FrameTime = 0;
int FPS = 0;

unsigned int mCurrentTick = 0;

float getSimulationTime();

// lab5

GLfloat pos[] = {0, 0, 0};

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
	FPS++;
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру

	// устанавливаем общую фоновую освещенность
	GLfloat globalAmbientColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);

	// включаем нулевой источник света
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	camera.apply();

	
	// вывод правого чайника
	graphicObjects[0].draw();
	//graphicObjects[0].printModelMatrix();
	//cin.get();
	// вывод левого чайника
	graphicObjects[1].draw();
	// вывод переднего чайника
	graphicObjects[2].draw();
	// вывод заднего чайника
	graphicObjects[3].draw();

	
	// смена переднего и заднего буферов
	glutSwapBuffers();
};
// функция симуляции - вызывается максимально часто
// через заранее неизвестные промежутки времени
// для чего регистрируется с помощью glutIdleFunc
void simulation()
{
	// определение времени симуляции
	float simulationTime = getSimulationTime();
	// передвижение камеры
	// устанавливаем признак того, что окно нуждается в перерисовке
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


// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", key);
	
	// для провекри класса камеры вызываем методы передвижения
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

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("Чайник");
	GraphicObject GraphicObject1;
	GraphicObject1.setPosition(vec3(4, 0, 0));
	GraphicObject1.setAngle(180);
	GraphicObject1.setСolor(vec3(1, 0, 0));
	graphicObjects.push_back(GraphicObject1);

	GraphicObject GraphicObject2;
	GraphicObject2.setPosition(vec3(-4, 0, 0));
	GraphicObject2.setAngle(0);
	GraphicObject2.setСolor(vec3(0, 0, 1));
	graphicObjects.push_back(GraphicObject2);

	GraphicObject GraphicObject3;
	GraphicObject3.setPosition(vec3(0, 0, 4));
	GraphicObject3.setAngle(90);
	GraphicObject3.setСolor(vec3(1, 1, 1));
	graphicObjects.push_back(GraphicObject3);

	GraphicObject GraphicObject4;
	GraphicObject4.setPosition(vec3(0, 0, -4));
	GraphicObject4.setAngle(270);
	GraphicObject4.setСolor(vec3(0, 1, 0));
	graphicObjects.push_back(GraphicObject4);


	// включаем режим расчета освещения
	glEnable(GL_LIGHTING);



	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию, которая будет вызвана как можно быстрее
	glutIdleFunc(simulation);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(keyboardFunc);

	// ИНИЦИАЛИЗАЦИЯ ДАННЫХ, НЕОБХОДИМЫХ ДЛЯ РАБОТЫ ПРОГРАММЫ:
// инициализация графических объектов


	// основной цикл обработки сообщений ОС
	glutMainLoop();

};