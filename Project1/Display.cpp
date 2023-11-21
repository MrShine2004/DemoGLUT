#include "Display.h"
#include "Data.h"
// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
	// включаем нулевой источник света
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);

	// включаем режим расчета освещения
	glEnable(GL_LIGHTING);
	// устанавливаем камеру
	camera.apply();
	// устанавливаем источник света
	light.apply(GL_LIGHT1);


	player->draw();
	planeGraphicObject.draw();
	for (auto& go : graphicObjects) {
		go.draw();
	}
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (mapObjects[i][j] != nullptr) {
				mapObjects[i][j]->draw();
			}
		}
	}
	// смена переднего и заднего буферов
	glutSwapBuffers();
};