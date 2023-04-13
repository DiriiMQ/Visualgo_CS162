//
// Created by dirii on 08/04/2023.
//

#include "NodeInfo.hpp"

NodeInfo::NodeInfo(sf::RenderWindow *window, std::string value, sf::Vector2f position) : BaseDraw(window) {
    this->position = position;
    this->node = new SingleNode(window, std::move(value), this->position);

    this->arrows[this->LEFT] = this->arrows[this->RIGHT] = nullptr;
    this->isInList = true;
}

void NodeInfo::render() {
    for (auto &arrow : this->arrows) {
        if (arrow != nullptr) {
            arrow->render();
        }
    }
    this->node->render();
}

void NodeInfo::initArrow(NodeInfo::ArrowType type, sf::Vector2f start, sf::Vector2f end) {
    this->arrows[type] = new Arrow(this->window, start, end);
}

void NodeInfo::setPosition(sf::Vector2f _position) {
    this->position = _position;
    this->node->setPosition(this->position);
    for (auto &arrow : this->arrows) {
        if (arrow != nullptr) {
            arrow->setPosition(this->position);
        }
    }
}

void NodeInfo::toggleActiveColorNode() {
    this->node->toggleActiveColor();
}

void NodeInfo::toggleActiveColorArrow(NodeInfo::ArrowType type) {
    this->arrows[type]->toggleActiveColor();
}

void NodeInfo::resetColorNode() {
    this->node->resetColor();
}

void NodeInfo::resetColorArrow(NodeInfo::ArrowType type) {
    this->arrows[type]->resetColor();
}

void NodeInfo::reset() {
    this->resetColorNode();
    this->resetColorArrow(this->LEFT);
    this->resetColorArrow(this->RIGHT);
    this->position.y = constants::NodeInfo::originNode.y;
    this->setPosition(this->position);
}

void NodeInfo::setStartArrow(NodeInfo::ArrowType type, sf::Vector2f start) {
    this->node->setPosition(this->position);
    for (auto &arrow : this->arrows) {
        if (arrow != nullptr) {
            arrow->setPosition(this->position);
        }
    }
}

sf::Vector2f NodeInfo::getPosition() {
    return this->position;
}
