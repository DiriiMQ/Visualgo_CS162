//
// Created by dirii on 10/04/2023.
//

#ifndef VISUALGO_CS162_SINGLENODE_HPP
#define VISUALGO_CS162_SINGLENODE_HPP

#include "Constants.hpp"
#include "BaseDraw.hpp"
#include <iostream>

class SingleNode : public BaseDraw{
private:
    sf::CircleShape circle;
    sf::Text label;
    sf::Font font;
    std::string value;

public:
    SingleNode(sf::RenderWindow* window, std::string value, sf::Vector2f position);
    void render() override;
};

#endif //VISUALGO_CS162_SINGLENODE_HPP
