#include <windows.h>

#include <iostream>
#include <vector>

#include <cstdlib> // ��� ������� rand() � srand()

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

// ���������� ������������ ���� ����������� ����������
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
#include "GameObject.h"
#include "Mesh.h"
#include "GameObjectFactory.h"

// ������ ����������� ��������
vector<GraphicObject> graphicObjects;
vector<GameObject> gameObjects;
GameObjectFactory gameObjectFactory;
shared_ptr<GameObject> player;
// ����� ������������
	int passabilityMap[21][21] = {
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
	3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
	3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
	3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
	3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
	3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
	3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
	3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
	3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
	3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
	3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
	3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
	3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
	3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
	3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
	3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
	3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
	3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
	3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	};
	// ������ ������� �������� ������������� �� �����
	std::shared_ptr<GameObject> mapObjects[21][21];
	// ����������� ������ ��� ��������� (������� ������)
	GraphicObject planeGraphicObject;



	float FrameTime = 0;
	int FPS = 0;

	float mCurrentTick = 0;
	float Xvec = 0;

	// lab5

	vec3 pos{ -100,100,100 };
	bool direct = 0;


	Light light;

	Camera camera; // �������� ������� ������
// ������� ��� ������������� ���� ����� ������ (������, ������� � �.�.)
void initData()
{
	// ������������� ������� ������� �������� � ��������� ������ �� ����� JSON
	bool result = gameObjectFactory.init("C:\\Users\\alexy\\Desktop\\Univer\\3curs\\AOCG\\Project1\\Debug\\Data\\GameObjectsDescription.json");
	if (!result) {
		std::cout << "������ ��� ������������� ������� ������� ��������." << std::endl;
		return; // ��� ���������� ����� ����������� �������� � ������ ������ �������������
	}

	// �������� �������� ��� �����
	for (int i = 0; i < 21; ++i) {
		for (int j = 0; j < 21; ++j) {
			switch (passabilityMap[i][j]) {
			case 1:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, j);
				break;
			case 2:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, j);
				break;
			case 3:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, j);
				break;
			default:
				mapObjects[i][j] = nullptr;
				break;
			}
		}
	}
	// ������������� �������� �����
	player = gameObjectFactory.create(GameObjectType::PLAYER, 19, 1);

	// ������������� ���������
	planeGraphicObject.setPosition(vec3(0, 0, 0));
	shared_ptr<Mesh> planeMesh = make_shared<Mesh>();
	planeMesh->load("C:\\Users\\alexy\\Desktop\\Univer\\3curs\\AOCG\\Project1\\Debug\\Data\\Meshes\\HighPolyPlane.obj");
	planeGraphicObject.setMesh(planeMesh);
	shared_ptr<PhongMaterial> planeMaterial = make_shared<PhongMaterial>();
	planeMaterial->load("C:\\Users\\alexy\\Desktop\\Univer\\3curs\\AOCG\\Project1\\Debug\\Data\\Materials\\PlaneMaterial.txt");
	planeGraphicObject.setMaterial(planeMaterial);

}

float getSimulationTime()
{
	static LARGE_INTEGER oldtime;
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	LARGE_INTEGER delta;
	delta.QuadPart = time.QuadPart - oldtime.QuadPart;
	LARGE_INTEGER ticks;
	QueryPerformanceFrequency(&ticks);

	//QueryPerformanceCounter(&ticks);
	oldtime = time;
	return (double)delta.QuadPart / (double)ticks.QuadPart;
}

