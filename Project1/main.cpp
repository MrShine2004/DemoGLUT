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


// lab 5
#include "Light.h"
#include "PhongMaterial.h"
#include "Simulation.h"
#include "Display.h"


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

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", key);
	
	// для провекри класса камеры вызываем методы передвижения
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
	glutCreateWindow("Окно");
	
	initData();
	light.setPosition(pos);


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