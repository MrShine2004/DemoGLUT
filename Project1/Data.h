#pragma once
#include <windows.h>
#include <vector>
#include "GL/freeglut.h"
#include <glm/glm/glm.hpp>
#include "Camera.h"
#include "GraphicObject.h"

using namespace std;

// список графических объектов
extern std::vector<GraphicObject> graphicObjects;
// используемая камера
extern Camera camera;
// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData();


extern bool generateRandomColor;



extern  float r, g, b;

// список цветов
extern  float colorm[5][3];

extern float upx, upy, upz; //5, 5, 7.5,  gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);
extern float atx, aty, atz; //5, 5, 7.5,

extern bool rot1;
extern bool rot2;

extern bool rot1y;
extern bool rot2y;


// список цветов
extern vector<vec3> teapotColors;
extern int timer;
extern int color_num;
extern int FPS;

float getSimulationTime();