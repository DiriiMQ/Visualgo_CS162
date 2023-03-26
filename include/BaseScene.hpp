//
// Created by dirii on 23/03/2023.
//

#ifndef VISUALGO_CS162_BASESCENE_HPP
#define VISUALGO_CS162_BASESCENE_HPP

#include <SFML/Graphics.hpp>

class BaseScene{
private:
    sf::RenderWindow* window;
public:
    void setWindow(sf::RenderWindow* window);
    virtual void pollEvent() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif //VISUALGO_CS162_BASESCENE_HPP
