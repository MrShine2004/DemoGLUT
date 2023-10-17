#include "PhongMaterial.h"

PhongMaterial::PhongMaterial()
{
    // �������������� ��������� �� ���������
    ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
    specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    emission = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    shininess = 32.0f;
}

void PhongMaterial::setAmbient(glm::vec4 color)
{
    ambient = color;
}

void PhongMaterial::setDiffuse(glm::vec4 color)
{
    diffuse = color;
}

void PhongMaterial::setSpecular(glm::vec4 color)
{
    specular = color;
}

void PhongMaterial::setEmission(glm::vec4 color)
{
    emission = color;
}

void PhongMaterial::setShininess(float p)
{
    shininess = p;
}

void PhongMaterial::load(std::string filename)
{
    // ���������� �������� ���������� ��������� �� �����
    // ��� ����� ������� � ��������� ����, � ����� ���������� ��������� ���������.
    // ������:

    std::ifstream file(filename);

    // ���������� ��������� �� ����� � ���������� �� � ������������ � ����� ��������

    // ������ ������ ����������:
    // file >> ambient.x >> ambient.y >> ambient.z >> ambient.w;
    // file >> diffuse.x >> diffuse.y >> diffuse.z >> diffuse.w;
    // file >> specular.x >> specular.y >> specular.z >> specular.w;
    // file >> emission.x >> emission.y >> emission.z >> emission.w;
    // file >> shininess;
}

void PhongMaterial::apply()
{
    // ���������� ���������� ���������
    // ��� ������� �� ������������ ����������� ���������� (��������, OpenGL).
    // ����������� ��������� ��������� ��� ��������� ������� ��������� �����.
    // ��������, ��� OpenGL:

    // glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(ambient));
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(diffuse));
    // glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(specular));
    // glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(emission));
    // glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
