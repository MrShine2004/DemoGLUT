#pragma once
// ����������, ������� ����� ���������� � ����� ������ � ��� ������,
// ���� ����� ��� ��� �� ���� �������� � ���� ����.
// ������� �������������� ���������� �� ������������ � �� �������������.
// ����� ��� ������������� ������ ������������ �������

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "PhongMaterial.h"

#include "Mesh.h"

#include <sstream>


using namespace glm;

class GraphicObject
{
public:
	// �����������
	GraphicObject();
	GraphicObject(const vec3& position, float angle, const vec3& color, const mat4& modelMatrix);
	// ��������� � ��������� ������� �������
	void setPosition(vec3 position);
	vec3 getPosition();
	// ��������� � ��������� ���� �������� � ��������
	// ������� �������������� � �������������� ���������
	// ������ ��� Oy �� ������� �������
	void setAngle(float grad);
	float getAngle();
	// ��������� �������� ����� �������
	void set�olor(vec3 color);
	vec3 getColor();

	// ��������� ������������� ���������
	void setMaterial(std::shared_ptr<PhongMaterial> material);
	// ��������� ������������� ����
	void setMesh(std::shared_ptr<Mesh> mesh);

	// ������� ������
	void draw();
	void printModelMatrix();
private:
	// ������� ������� � ���������� ������� ���������
	vec3 position;
	// ���� �������� � �������������� ��������� (� ��������)
	float angle;
	// ���� ������
	vec3 color;
	// ������� ������ (������������ �������) - ���� �� ��������� ������ ���
	mat4 modelMatrix = {
		{-1.0, 0.0, 0.0, 0.0}, // ��� Ox
		{0.0, 1.0, 0.0, 0.0}, // ��� Oy
		{0.0, 0.0, -1.0, 0.0}, // ��� Oz
		{4.0, 0.0, 0.0, 1.0 } // ������� ������� (������ ������� ���������)};
	};
	GLfloat modelMatrix1[16] = { 
		-1.0, 0.0, 0.0, 0.0, // ��� Ox
		0.0, 1.0, 0.0, 0.0, // ��� Oy
		0.0, 0.0, -1.0, 0.0, // ��� Oz
		4.0, 0.0, 0.0, 1.0 // ������� ������� (������ ������� ���������)
	};
	// ������������ ��������
	std::shared_ptr<PhongMaterial> material;
	// ������������ ���
	std::shared_ptr<Mesh> mesh;
	// ������ ������� modelMatrix �� ������ position � angle
	void recalculateModelMatrix();
};