#include "Camera.h"
using namespace std;

Camera::Camera()
{
    // Начальные значения для позиции, углов и радиуса
    position = vec3(0.0f, 0.0f, 0.0f);
    angleX = 0.0f;
    angleY = 40.0f;
    r = 50.0f;
    recalculatePosition();
}

Camera::Camera(vec3 position)
{
    // Устанавливаем заданную позицию, остальные значения по умолчанию
    this->position = position;
    angleX = 0.0f;
    angleY = 0.0f;
    r = 1.0f;
    recalculatePosition();
}


Camera::Camera(float x, float y, float z)
{
    // Устанавливаем заданные координаты позиции, остальные значения по умолчанию
    position[0] = x;
    position[1] = y;
    position[2] = z;
    angleX = 0.0f;
    angleY = 0.0f;
    r = 1.0f;
    recalculatePosition();
}


// установка позиции камеры
void Camera::setPosition(vec3 position)
{
	// определяем радиус - расстояние от начала системы координат до заданной позиции
	r = length(position);
	// определяем вертикальный угол:
	// это угол между вектором из начала координат к наблюдателю (v1)
	// и проекцией этого вектора на горизонтальную плоскость (v2)
	// для определения угла используется скалярное произведение нормализованных векторов
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// аналогичным образом определяем горизонтальный угол:
	// это угол между проекцией (v2) и единичным вектором вдоль оси Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// пересчитываем позицию (для корректировок ошибок округления)
	recalculatePosition();
}
vec3 Camera::getPosition()
{
    cout << position[0] << " " << position[1] << " " << position[2] << " " << endl;
    return position;
}

void Camera::rotateLeftRight(float degree)
{
    // Изменяем горизонтальный угол
    angleX += degree;
    // Проверяем, чтобы горизонтальный угол оставался в диапазоне [-180, 180]
    if (angleX > 180.0f)
        angleX -= 360.0f;
    else if (angleX < -180.0f)
        angleX += 360.0f;
    // Пересчитываем позицию
    recalculatePosition();
}

void Camera::rotateUpDown(float degree)
{
    // Изменяем вертикальный угол
    angleY += degree;
    // Ограничиваем вертикальный угол в диапазоне [-90, 90]
    if (angleY > 60.0f)
        angleY = 60.0f;
    else if (angleY < -60.0f)
        angleY = -60.0f;
    // Пересчитываем позицию
    recalculatePosition();
}

void Camera::zoomInOut(float distance)
{
    // Изменяем радиус (расстояние до цели)
    r -= distance;
    // Ограничиваем радиус, чтобы он не стал отрицательным
    if (r < 0.0f)
        r = 0.0f;
    if (r > 60.0f)
        r = 60.0f;
    // Пересчитываем позицию
    recalculatePosition();
}

void Camera::apply()
{
    glMatrixMode(GL_MODELVIEW);
    // Устанавливаем матрицу вида
    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}

void Camera::recalculatePosition()
{
    // Рассчитываем новую позицию камеры на основе радиуса и углов
    float radiansX = radians(angleX);
    float radiansY = radians(angleY);
    position.x = r * sin(radiansX) * cos(radiansY);
    position.y = r * sin(radiansY);
    position.z = r * cos(radiansX) * cos(radiansY);
}