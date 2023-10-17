#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

// КЛАСС ДЛЯ РАБОТЫ С ИСТОЧНИКОМ СВЕТА
class Light
{
public:
    // Конструкторы
    Light();
    Light(glm::vec3 position);
    Light(float x, float y, float z);

    // Методы для установки параметров
    void setPosition(glm::vec3 position);
    void setAmbient(glm::vec4 color);
    void setDiffuse(glm::vec4 color);
    void setSpecular(glm::vec4 color);

    // Установка всех параметров источника света с заданным номером
    // Данная функция должна вызываться после установки камеры,
    // т.к. здесь устанавливается позиция источника света
    void apply(GLenum LightNumber = GL_LIGHT0);

private:
    // Позиция источника света
    glm::vec4 position;
    // Фоновая составляющая источника света
    glm::vec4 ambient;
    // Диффузная составляющая
    glm::vec4 diffuse;
    // Зеркальная составляющая
    glm::vec4 specular;
};
