//
// Created by dirii on 28/04/2023.
//

#include "Square.hpp"

Square::Square(sf::RenderWindow *window, std::string value, sf::Vector2f position)
        : BaseDraw(window) {
    this->value = std::move(value);

    this->square.setSize(sf::Vector2f(constants::Square::length, constants::Square::length));
    this->square.setFillColor(sf::Color::White);
    this->square.setOutlineThickness(constants::Square::outlineThickness);
    this->square.setOutlineColor(sf::Color::Black);
    sf::FloatRect bounds = this->square.getLocalBounds();
    this->square.setOrigin(bounds.left + bounds.width / 2.0f,bounds.top + bounds.height / 2.0f);
    this->square.setPosition(position);

    this->font.loadFromFile(constants::fontPath);
    this->label.setFont(this->font);
    this->label.setString(this->value);
    this->label.setCharacterSize(constants::Square::fontSize);
    this->label.setFillColor(sf::Color::Black);
    bounds = this->label.getLocalBounds();
    this->label.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    this->label.setPosition(position);
}

void Square::render() {
    switch (this->status) {
        case Status::active:
            this->square.setOutlineColor(constants::normalGreen);
            break;
        case Status::inactive:
            this->square.setOutlineColor(sf::Color::Black);
            break;
        case Status::chosen:
            this->square.setOutlineColor(constants::clickGreen);
            break;
    }
    this->window->draw(this->square);
    this->window->draw(this->label);
}

void Square::resetColor() {
    this->status = Status::inactive;
}

void Square::setText(std::string _value) {
    this->value = std::move(_value);
    this->label.setString(this->value);
    sf::FloatRect bounds = this->label.getLocalBounds();
    this->label.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    this->label.setPosition(this->square.getPosition());
}

void Square::setPosition(sf::Vector2f position) {
    this->square.setPosition(position);
    this->label.setPosition(position);
}

sf::Vector2f Square::getPosition() {
    return this->square.getPosition();
}

void Square::setStatus(Square::Status _status) {
    this->status = _status;
}

Square::Status Square::getStatus() {
    return this->status;
}
