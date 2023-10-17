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

// ����� ��� ������ � ���������� �����
class Light
{
public:
    // ������������
    Light();
    Light(glm::vec3 position);
    Light(float x, float y, float z);

    // ������ ��� ��������� ����������
    void setPosition(glm::vec3 position);
    void setAmbient(glm::vec4 color);
    void setDiffuse(glm::vec4 color);
    void setSpecular(glm::vec4 color);

    // ��������� ���� ���������� ��������� ����� � �������� �������
    // ������ ������� ������ ���������� ����� ��������� ������,
    // �.�. ����� ��������������� ������� ��������� �����
    void apply(GLenum LightNumber = GL_LIGHT0);

private:
    // ������� ��������� �����
    glm::vec4 position;
    // ������� ������������ ��������� �����
    glm::vec4 ambient;
    // ��������� ������������
    glm::vec4 diffuse;
    // ���������� ������������
    glm::vec4 specular;
};
