//
// Created by dirii on 08/04/2023.
//

#ifndef VISUALGO_CS162_NODEINFO_HPP
#define VISUALGO_CS162_NODEINFO_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "BaseDraw.hpp"
#include "SingleNode.hpp"

class NodeInfo : public BaseDraw {
private:
    sf::Vector2f position;
    SingleNode* node;

public:
    NodeInfo(sf::RenderWindow* window, std::string value, sf::Vector2f position);
    void render() override;
};

#endif //VISUALGO_CS162_NODEINFO_HPP
