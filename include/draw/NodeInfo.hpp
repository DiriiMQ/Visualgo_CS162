//
// Created by dirii on 08/04/2023.
//

#ifndef VISUALGO_CS162_NODEINFO_HPP
#define VISUALGO_CS162_NODEINFO_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "BaseDraw.hpp"
#include "SingleNode.hpp"
#include "Arrow.hpp"

class NodeInfo : public BaseDraw {
private:
    sf::Vector2f position;
    SingleNode* node;
    Arrow* arrows[2];

public:
    bool isInList;

    enum ArrowType {
        LEFT,
        RIGHT
    };
    NodeInfo(sf::RenderWindow* window, std::string value, sf::Vector2f position);
    void render() override;
    void initArrow(ArrowType type, sf::Vector2f start, sf::Vector2f end);
    void setPosition(sf::Vector2f _position);
    void setStartArrow(ArrowType type, sf::Vector2f start);
    sf::Vector2f getPosition();
    // can cac ham de to mau node va canh noi giua cac node
    void toggleActiveColorNode();
    void toggleActiveColorArrow(ArrowType type);
    void resetColorNode();
    void resetColorArrow(ArrowType type);
    void reset();
};

#endif //VISUALGO_CS162_NODEINFO_HPP
