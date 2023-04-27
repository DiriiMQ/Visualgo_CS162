//
// Created by dirii on 26/04/2023.
//

#include "BackArrow.hpp"

BackArrow::BackArrow(sf::RenderWindow *window, sf::Vector2f start, sf::Vector2f end) : BaseDraw(window) {
    this->isShow = false;

    this->points[0] = end;
    this->points[1] = start;
    this->points[2] = sf::Vector2f(
            this->points[0].x,
            this->points[0].y - constants::NodeInfo::offsetX
    );
    this->points[3] = sf::Vector2f(
            this->points[1].x,
            this->points[2].y
    );
    this->arrow = new Arrow(window, this->points[2], this->points[0]);

    this->rectangleTexture[0].loadFromFile("../assets/rectangle/rectangle_black.png");
    this->rectangleTexture[1].loadFromFile("../assets/rectangle/rectangle_orange.png");

    this->rectangleTexture[0].setRepeated(true);
    this->rectangleTexture[1].setRepeated(true);

    sf::Vector2i topLeftCorner = sf::Vector2i(
            static_cast<int>(this->rectangleTexture[0].getSize().x / 2.0 - constants::Arrow::sizeRectangle.x / 2.0),
            static_cast<int>(this->rectangleTexture[0].getSize().y / 2.0 - constants::Arrow::sizeRectangle.y / 2.0)
    );
    for (auto & rectangleSprite : this->rectangleSprites) {
        rectangleSprite.setTexture(this->rectangleTexture[0]);
        rectangleSprite.setTextureRect(sf::IntRect(
                topLeftCorner.x,
                topLeftCorner.y,
                constants::Arrow::sizeRectangle.x,
                constants::Arrow::sizeRectangle.y
        ));
    }

    this->setPosition(start, end);
}

void BackArrow::render() {
    if (this->isShow) {
        this->window->draw(this->rectangleSprites[0]);
        this->window->draw(this->rectangleSprites[1]);
        this->arrow->render();
    }
}

void BackArrow::show() {
    this->isShow = true;
}

void BackArrow::hide() {
    this->isShow = false;
}

void BackArrow::toggleActiveColorNode() {
    this->rectangleSprites[0].setTexture(this->rectangleTexture[1]);
    this->rectangleSprites[1].setTexture(this->rectangleTexture[1]);
    this->arrow->toggleActiveColor();
}

void BackArrow::resetColor() {
    this->rectangleSprites[0].setTexture(this->rectangleTexture[0]);
    this->rectangleSprites[1].setTexture(this->rectangleTexture[0]);
    this->arrow->resetColor();
}

void BackArrow::setPosition(sf::Vector2f start, sf::Vector2f end) {
    this->points[0] = end;
    this->points[1] = start;
    if (end == start) {
        this->hide();
        return;
    }
    this->points[2] = sf::Vector2f(
            this->points[0].x,
            this->points[0].y - constants::NodeInfo::offsetX
    );
    this->points[3] = sf::Vector2f(
            this->points[1].x,
            this->points[2].y
    );
    this->arrow->setPositions(this->points[2], this->points[0], false);
    this->autoRotate();
    this->autoScale();
}

void BackArrow::autoScale() {
    float length = sqrtf(
            powf(this->points[3].x - this->points[2].x, 2) + powf(this->points[3].y - this->points[2].y, 2)
            );
    this->rectangleSprites[0].setScale(
            length / this->rectangleSprites[0].getLocalBounds().width,
            constants::Arrow::defaultScaleRectangle.y
    );
    length = sqrtf(
            powf(this->points[3].x - this->points[1].x, 2) + powf(this->points[3].y - this->points[1].y, 2)
            );
    this->rectangleSprites[1].setScale(
            length / this->rectangleSprites[1].getLocalBounds().width,
            constants::Arrow::defaultScaleRectangle.y
    );
    this->rectangleSprites[0].setOrigin(
            this->rectangleSprites[0].getLocalBounds().width / 2.0f,
            0
    );
    this->rectangleSprites[1].setOrigin(
            this->rectangleSprites[1].getLocalBounds().width,
            this->rectangleSprites[1].getLocalBounds().height / 2.0f
    );
    this->rectangleSprites[0].setPosition(
            (this->points[3].x + this->points[2].x) / 2.0f,
            (this->points[3].y + this->points[2].y) / 2.0f
            );
    this->rectangleSprites[1].setPosition(this->points[1]);
}

void BackArrow::autoRotate() {
    sf::Vector2f vector2point = this->points[3] - this->points[2];
    float angle = atan2f(vector2point.y, vector2point.x) * 180.0f / (float)M_PI;
    this->rectangleSprites[0].setRotation(angle);
    vector2point = this->points[1] - this->points[3];
    angle = atan2f(vector2point.y, vector2point.x) * 180.0f / (float)M_PI;
    this->rectangleSprites[1].setRotation(angle);
}
