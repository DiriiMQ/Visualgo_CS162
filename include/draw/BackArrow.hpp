//
// Created by dirii on 26/04/2023.
//

#ifndef VISUALGO_CS162_BACKARROW_HPP
#define VISUALGO_CS162_BACKARROW_HPP

#include "Arrow.hpp"
#include "Constants.hpp"

class BackArrow : public BaseDraw {
private:
    sf::Vector2f points[4];
    sf::Texture rectangleTexture[2];
    sf::Sprite rectangleSprites[2];
    Arrow* arrow;
    bool isShow;

public:
    BackArrow(sf::RenderWindow* window, sf::Vector2f start, sf::Vector2f end);
    void render() override;

    void autoScale();
    void autoRotate();

    void toggleActiveColorNode();
    void resetColor();

    void setPosition(sf::Vector2f start, sf::Vector2f end);

    void show();
    void hide();
};

#endif //VISUALGO_CS162_BACKARROW_HPP
