//
// Created by dirii on 12/04/2023.
//

#include "LinkedList.hpp"

LinkedList::LinkedList(sf::RenderWindow *window) {
    this->window = window;
    this->size = 0;
}

void LinkedList::addNode(NodeInfo *node) {

}

void LinkedList::removeNode(int index) {

}

void LinkedList::clear() {
    for (auto &node : this->nodes){
        delete node;
    }
    this->nodes.clear();
    this->size = 0;
}

void LinkedList::render() {
    for (auto &node : this->nodes){
        node->render();
    }
}

int LinkedList::getSize() const {
    return this->size;
}

NodeInfo *LinkedList::getNode(int index) {
    return this->nodes[index];
}

LinkedList::LinkedList(sf::RenderWindow* window, int size) {
    this->window = window;
    this->size = size;
    this->nodes.resize(size);
    for (int i = 0; i < size; i++){
        this->nodes[i] = new NodeInfo(
                this->window,
                std::to_string(Random::randomInt(0, 99)),
                constants::NodeInfo::originNode
                );
        this->nodes[i]->setPosition(
                sf::Vector2f(
                        constants::NodeInfo::originNode.x + static_cast<float>(i) * constants::NodeInfo::offsetX,
                        constants::NodeInfo::originNode.y
                        ));
        if (i > 0){
            this->nodes[i - 1]->initArrow(
                    NodeInfo::RIGHT,
                    this->nodes[i - 1]->getPosition(),
                    this->nodes[i]->getPosition()
                    );
        }
    }
}

LinkedList::LinkedList(sf::RenderWindow *window, std::vector<std::string> values) {
    this->window = window;
    this->size = static_cast<int>(values.size());
    this->nodes.resize(this->size);
    for (int i = 0; i < this->size; i++){
        this->nodes[i] = new NodeInfo(
                this->window,
                values[i],
                constants::NodeInfo::originNode
                );
        this->nodes[i]->setPosition(
                sf::Vector2f(
                        constants::NodeInfo::originNode.x + static_cast<float>(i) * constants::NodeInfo::offsetX,
                        constants::NodeInfo::originNode.y
                        ));
        if (i > 0){
            this->nodes[i - 1]->initArrow(
                    NodeInfo::RIGHT,
                    this->nodes[i - 1]->getPosition(),
                    this->nodes[i]->getPosition()
                    );
        }
    }
}
