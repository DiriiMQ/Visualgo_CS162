//
// Created by dirii on 08/04/2023.
//

#include "NodeInfo.hpp"

NodeInfo::NodeInfo(sf::RenderWindow *window, std::string value, sf::Vector2f position) : BaseDraw(window) {
    this->position = position;
    this->node = new SingleNode(window, std::move(value), this->position);

}

void NodeInfo::render() {
    this->node->render();
}
