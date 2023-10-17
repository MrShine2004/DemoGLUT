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

using namespace glm;

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterial
{
public:
	// конструктор по умолчанию
	PhongMaterial();
	// задание параметров материала
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	// загрузка параметров материала из внешнего текстового файла
	void load(std::string filename);
	// установка всех параметров материала
	void apply();
private:
	// фоновая составляющая
	vec4 ambient;
	// диффузная составляющая
	vec4 diffuse;
	// зеркальная составляющая
	vec4 specular;
	// самосвечение
	vec4 emission;
	// степень отполированности
	float shininess;
};
