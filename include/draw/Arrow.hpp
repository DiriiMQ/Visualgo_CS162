//
// Created by dirii on 08/04/2023.
//

#ifndef VISUALGO_CS162_ARROW_HPP
#define VISUALGO_CS162_ARROW_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "BaseDraw.hpp"
#include "Constants.hpp"

class Arrow : public BaseDraw{
private:
    sf::Vector2f points[2];
    sf::Texture arrowTexture[2];
    sf::Sprite arrowSprite;
    float length;
    sf::Texture rectangleTexture[2];
    sf::Sprite rectangleSprite;

public:
    Arrow(sf::RenderWindow* window, sf::Vector2f start, sf::Vector2f end);
    void render() override;
    void toggleActiveColor();
    void resetColor();
    void setPosition(sf::Vector2f start);
    void setMid();
    void autoRotate();
    void autoScale();
};

#endif //VISUALGO_CS162_ARROW_HPP
