//
// Created by dirii on 25/03/2023.
//

#include "Stuff.hpp"

void Button::init() {
    this->isHover = this->isClick = false;

    this->button.setSize(this->size);
    this->button.setFillColor(this->color);
    this->button.setPosition(this->position);

    // set rounded corners
    this->button.setCornerPointCount(constants::CORNER_POINT_COUNT_BUTTON);
    this->button.setCornersRadius(constants::CORNER_RADIUS_BUTTON);


    this->text.setFont(this->font);
    this->text.setString(this->textString);
    this->text.setCharacterSize(this->textSize);
    this->text.setFillColor(this->textColor);
    this->text.setPosition(this->position.x + this->size.x / 2.0 - this->text.getGlobalBounds().width / 2.0,
                           this->position.y + this->size.y / 2.0 - this->text.getGlobalBounds().height / 1.1);
}

Button::Button(sf::RenderWindow *window, sf::Vector2f position, sf::Vector2f size,
               std::string textString, std::string changedTextString, int textSize,
               sf::Color textColor, sf::Color color, sf::Color hoverColor, sf::Color clickColor) {
    this->window = window;
    this->position = position;
    this->size = size;
    this->textString = textString;
    this->changedTextString = changedTextString;
    this->textSize = textSize;
    this->color = color;
    this->textColor = textColor;
    this->hoverColor = hoverColor;
    this->clickColor = clickColor;
    this->font.loadFromFile(constants::fontPath);

    this->init();
}

bool Button::pollEvent(sf::Vector2f mousePosView){
    bool hasClicked = false;

    if (this->isHover and this->isClick and !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        hasClicked = true;
        std::swap(this->textString, this->changedTextString);
    }

    this->isHover = this->button.getGlobalBounds().contains(mousePosView);
    this->isClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    return hasClicked;
}

void Button::update() {
    if (this->isHover) {
        this->button.setFillColor(this->hoverColor);

        if (this->isClick) {
            this->button.setFillColor(this->clickColor);
        }
    } else {
        this->button.setFillColor(this->color);
    }

    this->text.setString(this->textString);
}

void Button::render() {
    this->window->draw(this->button);
    this->window->draw(this->text);
}

bool Button::checkClicked() const {
    return this->isClick and this->isHover;
}

std::string Button::getTextString() const {
    return this->textString;
}

void Button::setColor(sf::Color color) {
    this->color = color;
}

Button::Button() {

}
