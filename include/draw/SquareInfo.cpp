//
// Created by dirii on 28/04/2023.
//

#include "SquareInfo.hpp"

SquareInfo::SquareInfo(sf::RenderWindow *window, std::string value, sf::Vector2f position) : BaseDraw(window) {
    this->position = position;
    this->square = new Square(window, value, position);
    this->values[0] = std::move(value);
    this->values[1] = "";
    this->isPrintPreVal = false;

    this->title.setFont(this->square->font);
    this->title.setCharacterSize(20);
    this->title.setFillColor(sf::Color::Black);
}

void SquareInfo::render() {
    if (this->square->getStatus() != Square::Status::hidden) {
        this->square->render();
        this->window->draw(this->title);
    }
}

void SquareInfo::setValue(std::string value) {
    this->values[1] = this->values[0];
    this->values[0] = std::move(value);
}

void SquareInfo::update() {
    if (this->isPrintPreVal)
        this->square->setText(this->values[1]);
    else
        this->square->setText(this->values[0]);
}

void SquareInfo::setTitle(const std::string& _title) {
    this->title.setString(_title);
    sf::FloatRect bounds = this->title.getLocalBounds();
    this->title.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    this->title.setPosition(this->position.x, this->position.y + constants::TitleNode::offsetY);
}

void SquareInfo::resetTitle() {
    this->title.setString("");
}

void SquareInfo::reset() {
    this->resetTitle();
    this->square->resetColor();
    this->isPrintPreVal = false;
}

void SquareInfo::setStatus(Square::Status _status) {
    this->square->setStatus(_status);
}

std::string SquareInfo::getValue() {
    return this->values[0];
}

void SquareInfo::setPrintPreVal(bool _isPrintPreVal) {
    this->isPrintPreVal = _isPrintPreVal;
}

Square::Status SquareInfo::getStatus() {
    return this->square->getStatus();
}
