#include "Display.h"
#include "Data.h"
// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void display(void)
{
	// �������� ������� �������� �����
	// �������� ����� ����� � ����� �������
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);

	// �������� ����� ������� ���������
	glEnable(GL_LIGHTING);
	// ������������� ������
	camera.apply();
	// ������������� �������� �����
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
	// ����� ��������� � ������� �������
	glutSwapBuffers();
};