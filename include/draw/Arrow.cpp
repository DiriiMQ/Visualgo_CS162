//
// Created by dirii on 08/04/2023.
//

#include "Arrow.hpp"

Arrow::Arrow(sf::RenderWindow *window, sf::Vector2f start, sf::Vector2f end) : BaseDraw(window) {
    this->points[0] = start;
    this->points[1] = end;

    this->arrowTexture[0].loadFromFile("../assets/arrow/arrow_black.png");
    this->arrowTexture[1].loadFromFile("../assets/arrow/arrow_orange.png");

    this->arrowTexture[0].setSmooth(true);
    this->arrowTexture[1].setSmooth(true);

    this->arrowSprite.setTexture(this->arrowTexture[0]);
    sf::Vector2i topLeftCorner(
            static_cast<int>(this->arrowTexture[0].getSize().x / 2.0 - constants::Arrow::sizeArrow.x / 2.0),
            static_cast<int>(this->arrowTexture[0].getSize().y / 2.0 - constants::Arrow::sizeArrow.y / 2.0)
    );
    this->arrowSprite.setTextureRect(sf::IntRect(
            topLeftCorner.x,
            topLeftCorner.y,
            constants::Arrow::sizeArrow.x,
            constants::Arrow::sizeArrow.y
    ));

    this->autoScale();
    this->autoRotate();

    this->rectangleTexture[0].loadFromFile("../assets/rectangle/rectangle_black.png");
    this->rectangleTexture[1].loadFromFile("../assets/rectangle/rectangle_orange.png");
    topLeftCorner = sf::Vector2i(
            static_cast<int>(this->rectangleTexture[0].getSize().x / 2.0 - constants::Arrow::sizeRectangle.x / 2.0),
            static_cast<int>(this->rectangleTexture[0].getSize().y / 2.0 - constants::Arrow::sizeRectangle.y / 2.0)
    );
    this->rectangleSprite.setTexture(this->rectangleTexture[0]);
    this->rectangleSprite.setTextureRect(sf::IntRect(
            topLeftCorner.x,
            topLeftCorner.y,
            constants::Arrow::sizeRectangle.x,
            constants::Arrow::sizeRectangle.y
    ));
    this->rectangleSprite.setScale(
            constants::Arrow::defaultScaleRectangle.x,
            constants::Arrow::defaultScaleRectangle.y
            );
    this->rectangleSprite.setOrigin(
            0,
            this->rectangleSprite.getLocalBounds().height / 2.0f
    );
    this->rectangleSprite.setPosition(sf::Vector2f(50, 200));
//    this->rectangleSprite.setRotation(angle);
}

void Arrow::render() {
    this->window->draw(this->arrowSprite);
//    this->window->draw(this->rectangleSprite);
}

void Arrow::toggleActiveColor() {
    this->arrowSprite.setTexture(this->arrowTexture[1]);
    this->rectangleSprite.setTexture(this->rectangleTexture[1]);
}

void Arrow::resetColor() {
    this->arrowSprite.setTexture(this->arrowTexture[0]);
    this->rectangleSprite.setTexture(this->rectangleTexture[0]);
}

void Arrow::setPosition(sf::Vector2f start) {
    this->points[0] = start;
    this->arrowSprite.setPosition(this->points[0]);
    this->autoScale();
    this->autoRotate();
}

void Arrow::autoRotate() {
    sf::Vector2f vector2point = this->points[1] - this->points[0];
    auto angle = static_cast<float>(atan2(vector2point.y, vector2point.x) * 180 / M_PI);
    this->arrowSprite.setRotation(angle);
}

void Arrow::autoScale() {
    this->length = static_cast<float>(
            sqrt(
                    pow(this->points[1].x - this->points[0].x, 2) + pow(this->points[1].y - this->points[0].y, 2)
            ) - constants::NodeInfo::radius
            );
    this->arrowSprite.setScale(
            this->length / this->arrowSprite.getLocalBounds().width,
            constants::Arrow::defaultScaleArrow.y
    );
    this->arrowSprite.setOrigin(
            0,
            this->arrowSprite.getLocalBounds().height / 2.0f
    );
    this->arrowSprite.setPosition(this->points[0]);
}

void Arrow::setMid() {
    this->points[0] = sf::Vector2f(
            (this->points[0].x + this->points[1].x) / 2.0f,
            (this->points[0].y + this->points[1].y) / 2.0f
    );
    this->arrowSprite.setPosition(this->points[0]);
}
