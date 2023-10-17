#include "Light.h"

// КЛАСС ДЛЯ РАБОТЫ С ИСТОЧНИКОМ СВЕТА
Light::Light()
{
    // Инициализируем параметры по умолчанию
    position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
    specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

Light::Light(glm::vec3 position)
{
    // Инициализируем параметры источника света, позицию берем из аргумента
    this->position = glm::vec4(position, 1.0f);
    ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
    specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

Light::Light(float x, float y, float z)
{
    // Инициализируем параметры источника света, позицию берем из аргументов
    position = glm::vec4(x, y, z, 1.0f);
    ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
    specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void Light::setPosition(glm::vec3 position)
{
    this->position = glm::vec4(position, 1.0f);
}

void Light::setAmbient(glm::vec4 color)
{
    ambient = color;
}

void Light::setDiffuse(glm::vec4 color)
{
    diffuse = color;
}

void Light::setSpecular(glm::vec4 color)
{
    specular = color;
}

void Light::apply(GLenum LightNumber) {
    // Применяем параметры источника света с заданным номером
    glLightfv(LightNumber, GL_POSITION, &position[0]);
    glLightfv(LightNumber, GL_AMBIENT, &ambient[0]);
    glLightfv(LightNumber, GL_DIFFUSE, &diffuse[0]);
    glLightfv(LightNumber, GL_SPECULAR, &specular[0]);
}