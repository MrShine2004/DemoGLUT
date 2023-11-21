#include "GameObject.h"

GameObject::GameObject() {
    
}

void GameObject::setGraphicObject(const GraphicObject& graphicObject) {
    //std::cout << "Position = " << getPosition().x << " " << getPosition().y << std::endl;
    this->graphicObject = graphicObject;
}

void GameObject::setPosition(int x, int y) {
    //position.x = x;
    //position.y = y;
    graphicObject.setPosition(vec3(x, 0.5, y));
}

void GameObject::setPosition(ivec2 position) {
    this->position = position;
}

ivec2 GameObject::getPosition() {
    return position;
}

void GameObject::draw() {
    graphicObject.draw();
}

