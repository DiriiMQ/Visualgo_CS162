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
protected:
    sf::Vector2f points[2];
    sf::Texture arrowTexture[2];
    sf::Sprite arrowSprite;
    float length;
    bool hasSetMid;

public:
    Arrow(sf::RenderWindow* window, sf::Vector2f start, sf::Vector2f end);
    void render() override;
    void toggleActiveColor();
    void resetColor();
    void setStart(sf::Vector2f start, bool needSetMid);
    void setPositions(sf::Vector2f start, sf::Vector2f end, bool needSetMid);
    void setMid();
    void autoRotate();
    void autoScale();

    void hide();
    void show();
};

#endif //VISUALGO_CS162_ARROW_HPP
