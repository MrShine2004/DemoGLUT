#include "Simulation.h"
#include "Data.h"

// ������� ��������� - ���������� ����������� �����
// ����� ������� ����������� ���������� �������
// ��� ���� �������������� � ������� glutIdleFunc
void simulation()
{
	// ����������� ������� ���������
	float simulationTime = getSimulationTime();
	// ������������ ������
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
	FrameTime += simulationTime;
	FPS++;
	if (FrameTime >= 1) {
		std::stringstream ss;
		ss << FPS << " FPS";
		std::string fpsString = ss.str();
		//cout << "FPS = " << FPS << endl; 
		glutSetWindowTitle(fpsString.c_str());
		FPS = 0;
		FrameTime = 0;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		camera.rotateLeftRight(-100.0 * simulationTime);
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		camera.rotateLeftRight(100.0 * simulationTime);
	}
	if (GetAsyncKeyState(VK_UP)) {
		camera.rotateUpDown(100.0 * simulationTime);
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		camera.rotateUpDown(-100.0 * simulationTime);
	}
	if (GetAsyncKeyState(VK_CONTROL)) {
		camera.zoomInOut(-20 * simulationTime);
	}
	if (GetAsyncKeyState(VK_SHIFT)) {
		camera.zoomInOut(20 * simulationTime);
	}
};