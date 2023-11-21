#include "Camera.h"
using namespace std;

Camera::Camera()
{
    // ��������� �������� ��� �������, ����� � �������
    position = vec3(0.0f, 0.0f, 0.0f);
    angleX = 0.0f;
    angleY = 40.0f;
    r = 50.0f;
    recalculatePosition();
}

Camera::Camera(vec3 position)
{
    // ������������� �������� �������, ��������� �������� �� ���������
    this->position = position;
    angleX = 0.0f;
    angleY = 0.0f;
    r = 1.0f;
    recalculatePosition();
}


Camera::Camera(float x, float y, float z)
{
    // ������������� �������� ���������� �������, ��������� �������� �� ���������
    position[0] = x;
    position[1] = y;
    position[2] = z;
    angleX = 0.0f;
    angleY = 0.0f;
    r = 1.0f;
    recalculatePosition();
}


// ��������� ������� ������
void Camera::setPosition(vec3 position)
{
	// ���������� ������ - ���������� �� ������ ������� ��������� �� �������� �������
	r = length(position);
	// ���������� ������������ ����:
	// ��� ���� ����� �������� �� ������ ��������� � ����������� (v1)
	// � ��������� ����� ������� �� �������������� ��������� (v2)
	// ��� ����������� ���� ������������ ��������� ������������ ��������������� ��������
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// ����������� ������� ���������� �������������� ����:
	// ��� ���� ����� ��������� (v2) � ��������� �������� ����� ��� Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// ������������� ������� (��� ������������� ������ ����������)
	recalculatePosition();
}
vec3 Camera::getPosition()
{
    cout << position[0] << " " << position[1] << " " << position[2] << " " << endl;
    return position;
}

void Camera::rotateLeftRight(float degree)
{
    // �������� �������������� ����
    angleX += degree;
    // ���������, ����� �������������� ���� ��������� � ��������� [-180, 180]
    if (angleX > 180.0f)
        angleX -= 360.0f;
    else if (angleX < -180.0f)
        angleX += 360.0f;
    // ������������� �������
    recalculatePosition();
}

void Camera::rotateUpDown(float degree)
{
    // �������� ������������ ����
    angleY += degree;
    // ������������ ������������ ���� � ��������� [-90, 90]
    if (angleY > 60.0f)
        angleY = 60.0f;
    else if (angleY < -60.0f)
        angleY = -60.0f;
    // ������������� �������
    recalculatePosition();
}

void Camera::zoomInOut(float distance)
{
    // �������� ������ (���������� �� ����)
    r -= distance;
    // ������������ ������, ����� �� �� ���� �������������
    if (r < 0.0f)
        r = 0.0f;
    if (r > 60.0f)
        r = 60.0f;
    // ������������� �������
    recalculatePosition();
}

void Camera::apply()
{
    glMatrixMode(GL_MODELVIEW);
    // ������������� ������� ����
    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}

void Camera::recalculatePosition()
{
    // ������������ ����� ������� ������ �� ������ ������� � �����
    float radiansX = radians(angleX);
    float radiansY = radians(angleY);
    position.x = r * sin(radiansX) * cos(radiansY);
    position.y = r * sin(radiansY);
    position.z = r * cos(radiansX) * cos(radiansY);
}