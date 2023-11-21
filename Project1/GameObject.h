	#pragma once
	#include <fstream>
	#include <string>
	#include <windows.h>
	#include <stdio.h>
	#include <iostream>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "GL/freeglut.h"
	#include <glm/glm/glm.hpp>
	#include <glm/glm/gtc/matrix_transform.hpp>
	#include <glm/glm/gtc/type_ptr.hpp>
	#include <vector>
	#include "GraphicObject.h"

	using namespace glm;
	// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ИГРОВОГО ОБЪЕКТА
	class GameObject
	{
	public:
		// конструктор
		GameObject();
		// установка используемого графического объекта
		// происходит копирование переданного объекта для последующего использования
		void setGraphicObject(const GraphicObject& graphicObject);
		// установка логических координат (два перегруженных метода для удобства)
		void setPosition(int x, int y);
		void setPosition(ivec2 position);
		// получение текущих логических координат
		ivec2 getPosition();
		// вывод игрового объекта на экран
		void draw(void);
	private:
		// логические координаты игрового объекта
		ivec2 position;
		// графический объект (для вывода на экран)
		GraphicObject graphicObject;
	};