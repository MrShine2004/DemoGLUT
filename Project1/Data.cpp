#include "Data.h"
#include "vector"

// используемые пространства имен
using namespace glm;
using namespace std;
// список графических объектов
vector<GraphicObject> graphicObjects;
// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData()
{
	// инициализация графических объектов
	GraphicObject GraphicObject1;
	GraphicObject1.setPosition(vec3(4, 0, 0));
	GraphicObject1.setAngle(180);
	GraphicObject1.setСolor(vec3(1, 0, 0));
	graphicObjects.push_back(GraphicObject1);

	GraphicObject GraphicObject2;
	GraphicObject2.setPosition(vec3(-4, 0, 0));
	GraphicObject2.setAngle(0);
	GraphicObject2.setСolor(vec3(0, 0, 1));
	graphicObjects.push_back(GraphicObject2);

	GraphicObject GraphicObject3;
	GraphicObject3.setPosition(vec3(0, 0, 4));
	GraphicObject3.setAngle(90);
	GraphicObject3.setСolor(vec3(1, 1, 1));
	graphicObjects.push_back(GraphicObject3);

	GraphicObject GraphicObject4;
	GraphicObject4.setPosition(vec3(0, 0, -4));
	GraphicObject4.setAngle(270);
	GraphicObject4.setСolor(vec3(0, 1, 0));
	graphicObjects.push_back(GraphicObject4);
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

	//if (!QueryPerformanceCounter(&ticks))
	//{
	//	cout << "QueryPerformanceFrequency failed!\n";
	//}


	//QueryPerformanceCounter(&ticks);
	oldtime = time;
	return (double)delta.QuadPart / (double)ticks.QuadPart;
}
