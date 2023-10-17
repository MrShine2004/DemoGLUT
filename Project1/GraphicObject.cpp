#include "GraphicObject.h"
using namespace std;

GraphicObject::GraphicObject() = default;


GraphicObject::GraphicObject(const vec3& position, float angle, const vec3& color, const mat4& modelMatrix)
	: position(position), angle(angle), color(color), modelMatrix(modelMatrix)
{
}
// Установка и получение позиции объекта
void GraphicObject::setPosition(vec3 positions) {
	//cout << "Position (x y z) = ";
	//cin >> position[0] >> position[0] >> position[0];
	position[0] = positions[0];
	position[1] = positions[1];
	position[2] = positions[2];
	//GraphicObject::getPosition();
	cout << "\n";
};
vec3 GraphicObject::getPosition() {
	cout << "Position (x y z) = ";
	cout << position[0] << " " << position[1] << " " << position[2];
	cout << "\n";
	return position;
};
// Установка и получения угла поворота в градусах
// поворот осуществляется в горизонтальной плоскости
// вокруг оси Oy по часовой стрелке
void GraphicObject::setAngle(float grad) {
	//cout << "Angle = ";
	//cin >> angle;
	angle = grad / 180 * 3.14159;
	//GraphicObject::getAngle();
	cout << "\n";
};
float GraphicObject::getAngle() {
	//cout << "Angle = ";
	//cout << angle;
	//cout << "\n";
	return angle;
}
// Установка текущего цвета объекта
void GraphicObject::setСolor(vec3 colors) {
	//cout << "R = ";
	//cin >> color[0];
	//cout << "\n";

	//cout << "G = ";
	//cin >> color[1];
	//cout << "\n";

	//cout << "B = ";
	//cin >> color[2];
	color[0] = colors[0];
	color[1] = colors[1];
	color[2] = colors[2];
	GraphicObject::getColor();
	cout << "\n";
};
vec3 GraphicObject::getColor() {
	cout << "R = ";
	cout << color[0];
	cout << "\n";

	cout << "G = ";
	cout << color[1];
	cout << "\n";

	cout << "B = ";
	cout << color[2];
	cout << "\n";
	return color;
};

void GraphicObject::printModelMatrix() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << GraphicObject::modelMatrix[i][j] << " ";
		}
		cout << endl;
	}
}
// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix() {
	mat4 trans = translate(mat4(1.0f), position);
	mat4 rot = rotate(mat4(1.0f), getAngle(), vec3(0.0f, 1.0f, 0.0f));
	mat4 scal = scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
	modelMatrix = trans * rot * scal;
};
// Вывести объект
void GraphicObject::draw() {
	GraphicObject::recalculateModelMatrix();
	glPushMatrix();
	glMultMatrixf(&modelMatrix[0][0]);
	glColor3f(color[0], color[1], color[2]);
	glutSolidTeapot(1.0);
	glPopMatrix();
};


