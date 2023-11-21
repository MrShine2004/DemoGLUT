#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/gl.h>
#include <map>
using namespace std;

Mesh::Mesh() {
    // Конструктор класса Mesh
    // Здесь вы можете инициализировать члены класса, если это необходимо
}

void Mesh::load(std::string filename) {
    std::vector<glm::vec3> v;  // Геометрические координаты
    std::vector<glm::vec3> n;  // Нормали
    std::vector<glm::vec2> t;  // Текстурные координаты
    std::vector<glm::ivec3> fPoints;  // Индексы атрибутов для формирования вершин

    std::map<std::string, int> vertexToIndexTable;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            // Обработка геометрических координат
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            v.push_back(vertex);
        }
        else if (prefix == "vn") {
            // Обработка нормалей
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            n.push_back(normal);
        }
        else if (prefix == "vt") {
            // Обработка текстурных координат
            glm::vec2 texCoord;
            iss >> texCoord.x >> texCoord.y;
            t.push_back(texCoord);
        }
        else if (prefix == "f") {
            // Обработка индексов атрибутов для формирования вершин
            glm::ivec3 point1, point2, point3;
            iss >> point1.x;
            iss.ignore(1);
            iss >> point1.y;
            iss.ignore(1);
            iss >> point1.z;

            iss >> point2.x;
            iss.ignore(1);
            iss >> point2.y;
            iss.ignore(1);
            iss >> point2.z;

            iss >> point3.x;
            iss.ignore(1);
            iss >> point3.y;
            iss.ignore(1);
            iss >> point3.z;

            fPoints.push_back(point1);
            fPoints.push_back(point2);
            fPoints.push_back(point3);
        }
    }

    file.close();

    for (const auto& fPoint : fPoints) {
        std::string vertexKey = std::to_string(fPoint.x) + "/" + std::to_string(fPoint.y) + "/" + std::to_string(fPoint.z);
        //cout << vertexKey << endl;
        if (vertexToIndexTable.find(vertexKey) != vertexToIndexTable.end()) {
            indices.push_back(vertexToIndexTable[vertexKey]);
        }
        else {
            Vertex vertex;
            vertex.coord[0] = v[fPoint.x - 1].x;
            vertex.coord[1] = v[fPoint.x - 1].y;
            vertex.coord[2] = v[fPoint.x - 1].z;

            vertex.normal[0] = n[fPoint.z - 1].x;
            vertex.normal[1] = n[fPoint.z - 1].y;
            vertex.normal[2] = n[fPoint.z - 1].z;

            vertex.texCoord[0] = t[fPoint.y - 1].x;
            vertex.texCoord[1] = t[fPoint.y - 1].y;

            vertices.push_back(vertex);
            int newIndex = vertices.size() - 1;
            indices.push_back(newIndex);
            vertexToIndexTable[vertexKey] = newIndex;
        }
    }

    std::cout << "Количество геометрических координат: " << v.size() << std::endl;
    std::cout << "Количество нормалей: " << n.size() << std::endl;
    std::cout << "Количество текстурных координат: " << t.size() << std::endl;
    std::cout << "Количество индексов атрибутов для формирования вершин: " << fPoints.size() << std::endl;
}



void Mesh::draw() {
    if (vertices.empty()) {
        std::cerr << "Mesh is empty. Cannot draw." << std::endl;
        return;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].coord[0]);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), &vertices[0].normal[0]);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vertices[0].texCoord[0]);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, &indices[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
