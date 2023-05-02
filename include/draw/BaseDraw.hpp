//
// Created by dirii on 08/04/2023.
//

#ifndef VISUALGO_CS162_BASEDRAW_HPP
#define VISUALGO_CS162_BASEDRAW_HPP

#include <SFML/Graphics.hpp>

class BaseDraw{
protected:
    sf::RenderWindow* window;

public:
    explicit BaseDraw(sf::RenderWindow* window);


    virtual void render() = 0;
};

#endif //VISUALGO_CS162_BASEDRAW_HPP
