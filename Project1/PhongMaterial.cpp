#include "PhongMaterial.h"
#include <sstream>

using namespace std;


PhongMaterial::PhongMaterial()
{
    // Инициализируем параметры по умолчанию
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
    // Открываем файл для чтения
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Разбираем строку и извлекаем параметры
        std::istringstream lineStream(line);
        std::string parameter;
        lineStream >> parameter;

        if (parameter == "diffuse:")
        {
            lineStream >> diffuse[0] >> diffuse[1] >> diffuse[2] >> diffuse[3];
        }
        else if (parameter == "ambient:")
        {
            lineStream >> ambient.x >> ambient.y >> ambient.z >> ambient.w;
        }
        else if (parameter == "specular:")
        {
            lineStream >> specular.x >> specular.y >> specular.z >> specular.w;
        }
        else if (parameter == "emission:")
        {
            lineStream >> emission.x >> emission.y >> emission.z >> emission.w;
        }
        else if (parameter == "shininess:")
        {
            lineStream >> shininess;
        }
    }
    std::cout << "Material loaded from: " << filename << std::endl;  // Вывод сообщения о загрузке
    std::cout << "Ambient: " << ambient.x << " " << ambient.y << " " << ambient.z << " " << ambient.w << std::endl;
    std::cout << "Diffuse: " << diffuse[0] << " " << diffuse[1] << " " << diffuse[2] << " " << diffuse[3] << std::endl;
    std::cout << "Specular: " << specular.x << " " << specular.y << " " << specular.z << " " << specular.w << std::endl;
    std::cout << "Emission: " << emission.x << " " << emission.y << " " << emission.z << " " << emission.w << std::endl;
    std::cout << "Shininess: " << shininess << std::endl;
}



void PhongMaterial::apply()
{
    // Применение параметров материала
    // Это зависит от используемой графической библиотеки (например, OpenGL).
    // Используйте параметры материала для настройки свойств отражения света.
    // Например, для OpenGL:

    glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(ambient));
    glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(diffuse));
    glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(specular));
    glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(emission));
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
