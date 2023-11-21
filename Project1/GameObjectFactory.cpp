#include "GameObjectFactory.h"
#include <fstream>
#include <iostream>

using namespace std;

bool GameObjectFactory::init(std::string filename) {
    // Открыть JSON-файл для чтения
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Не удается открыть файл " << filename << std::endl;
        return false;
    }

    // Считать весь JSON-файл в строку
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonString = buffer.str();

    // Создать объект для парсинга JSON
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    if (document.HasParseError()) {
        std::cout << "Ошибка парсинга JSON: " << document.GetParseError() << std::endl;
        return false;
    }

    // Обработка разделов JSON и сохранение данных
    for (auto& type : { "LightObject", "HeavyObject", "BorderObject", "Player", "Bomb", "Monster" }) {
        if (document.HasMember(type) && document[type].IsObject()) {
            const rapidjson::Value& obj = document[type];

            // Получаем меш из JSON
            std::string meshPath = obj["mesh"].GetString();
            std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
            mesh->load(meshPath);

            // Получаем материал из JSON
            std::shared_ptr<PhongMaterial> material = std::make_shared<PhongMaterial>();

            // Получаем массивы чисел для каждой составляющей цвета из JSON
            const auto& diffuseArray = obj["material"]["diffuse"].GetArray();
            const auto& ambientArray = obj["material"]["ambient"].GetArray();
            const auto& specularArray = obj["material"]["specular"].GetArray();
            const auto& emissionArray = obj["material"]["emission"].GetArray();

            // Создаем объекты glm::vec4 для цветов и устанавливаем их
            glm::vec4 diffuseColor(
                diffuseArray[0].GetFloat(),
                diffuseArray[1].GetFloat(),
                diffuseArray[2].GetFloat(),
                diffuseArray[3].GetFloat()
            );

            glm::vec4 ambientColor(
                ambientArray[0].GetFloat(),
                ambientArray[1].GetFloat(),
                ambientArray[2].GetFloat(),
                ambientArray[3].GetFloat()
            );

            glm::vec4 specularColor(
                specularArray[0].GetFloat(),
                specularArray[1].GetFloat(),
                specularArray[2].GetFloat(),
                specularArray[3].GetFloat()
            );

            glm::vec4 emissionColor(
                emissionArray[0].GetFloat(),
                emissionArray[1].GetFloat(),
                emissionArray[2].GetFloat(),
                emissionArray[3].GetFloat()
            );

            // Устанавливаем полученные цвета для материала
            material->setDiffuse(diffuseColor);
            material->setAmbient(ambientColor);
            material->setSpecular(specularColor);
            material->setEmission(emissionColor);
            material->setShininess(obj["material"]["shininess"].GetFloat());

            // Добавляем меш и материал в вектора meshes и materials
            meshes.push_back(mesh);
            materials.push_back(material);
        }
    }

    return true;
}


std::shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y) {
    std::shared_ptr<GameObject> newGameObject = std::make_shared<GameObject>();

    switch (type) {
    case GameObjectType::LIGHT_OBJECT:
    case GameObjectType::HEAVY_OBJECT:
    case GameObjectType::BORDER_OBJECT:
    case GameObjectType::PLAYER:
    case GameObjectType::BOMB:
    case GameObjectType::MONSTER: {

        size_t index = static_cast<size_t>(type);
        if (index < meshes.size() && index < materials.size()) {
            // Создание графического объекта с полученным мешем и материалом
            GraphicObject graphicObj;
            graphicObj.setMesh(meshes[index]);
            graphicObj.setMaterial(materials[index]);

            // Установка графического объекта для нового игрового объекта
            newGameObject->setGraphicObject(graphicObj);
            // Установка позиции для нового игрового объекта
            newGameObject->setPosition(x - 10, y - 10);
        }
        else {
            std::cout << "Ошибка: Недостаточно данных для создания объекта" << std::endl;
            return nullptr;
        }
        break;
    }
    default:
        std::cout << "Неподдерживаемый тип игрового объекта" << std::endl;
        return nullptr;
    }

    return newGameObject;
}

