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
	// ����� ��� ������������� �������� �������
	class GameObject
	{
	public:
		// �����������
		GameObject();
		// ��������� ������������� ������������ �������
		// ���������� ����������� ����������� ������� ��� ������������ �������������
		void setGraphicObject(const GraphicObject& graphicObject);
		// ��������� ���������� ��������� (��� ������������� ������ ��� ��������)
		void setPosition(int x, int y);
		void setPosition(ivec2 position);
		// ��������� ������� ���������� ���������
		ivec2 getPosition();
		// ����� �������� ������� �� �����
		void draw(void);
	private:
		// ���������� ���������� �������� �������
		ivec2 position;
		// ����������� ������ (��� ������ �� �����)
		GraphicObject graphicObject;
	};