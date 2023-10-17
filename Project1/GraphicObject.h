#pragma once
// Инструкции, которые будут подключены к файлу только в том случае,
// если ранее они уже не были включены в этот файл.
// Никакие дополнительные объявления не используются и не анализируются.
// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
using namespace glm;

class GraphicObject
{
public:
	// Конструктор
	GraphicObject();
	GraphicObject(const vec3& position, float angle, const vec3& color, const mat4& modelMatrix);
	// Установка и получение позиции объекта
	void setPosition(vec3 position);
	vec3 getPosition();
	// Установка и получения угла поворота в градусах
	// поворот осуществляется в горизонтальной плоскости
	// вокруг оси Oy по часовой стрелке
	void setAngle(float grad);
	float getAngle();
	// Установка текущего цвета объекта
	void setСolor(vec3 color);
	vec3 getColor();
	// Вывести объект
	void draw();
	void printModelMatrix();
private:
	// Позиция объекта в глобальной системе координат
	vec3 position;
	// Угол поворота в горизонтальной плоскости (в градусах)
	float angle;
	// Цвет модели
	vec3 color;
	// Матрица модели (расположение объекта) - чтоб не вычислять каждый раз
	mat4 modelMatrix = {
		{-1.0, 0.0, 0.0, 0.0}, // ось Ox
		{0.0, 1.0, 0.0, 0.0}, // ось Oy
		{0.0, 0.0, -1.0, 0.0}, // ось Oz
		{4.0, 0.0, 0.0, 1.0 } // позиция объекта (начало системы координат)};
	};
	GLfloat modelMatrix1[16] = { 
		-1.0, 0.0, 0.0, 0.0, // ось Ox
		0.0, 1.0, 0.0, 0.0, // ось Oy
		0.0, 0.0, -1.0, 0.0, // ось Oz
		4.0, 0.0, 0.0, 1.0 // позиция объекта (начало системы координат)
	};
	// расчет матрицы modelMatrix на основе position и angle
	void recalculateModelMatrix();
};