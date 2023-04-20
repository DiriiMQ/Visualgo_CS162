//
// Created by dirii on 10/04/2023.
//

#include "SingleNode.hpp"

SingleNode::SingleNode(sf::RenderWindow *window, std::string value, sf::Vector2f position) : BaseDraw(window) {
    this->value = std::move(value);

    this->circle.setRadius(constants::NodeInfo::radius);
    this->circle.setFillColor(sf::Color::White);
    this->circle.setOutlineThickness(constants::NodeInfo::outlineThickness);
    this->circle.setOutlineColor(sf::Color::Black);
    this->circle.setPointCount(constants::NodeInfo::pointCount);
    sf::FloatRect bounds = this->circle.getLocalBounds();
    this->circle.setOrigin(bounds.left + bounds.width / 2.0f,bounds.top + bounds.height / 2.0f);
    this->circle.setPosition(position);

    this->font.loadFromFile(constants::fontPath);
    this->label.setFont(this->font);
    this->label.setString(this->value);
    this->label.setCharacterSize(constants::NodeInfo::fontSize);
    this->label.setFillColor(sf::Color::Black);
    bounds = this->label.getLocalBounds();
    this->label.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    this->label.setPosition(position);
}

void SingleNode::render() {
    this->window->draw(this->circle);
    this->window->draw(this->label);
}

void SingleNode::toggleActiveColor() {
    this->circle.setOutlineColor(constants::normalGreen);
}

void SingleNode::resetColor() {
    this->circle.setOutlineColor(sf::Color::Black);
}

void SingleNode::setPosition(sf::Vector2f position) {
    this->circle.setPosition(position);
    this->label.setPosition(position);
}

sf::Vector2f SingleNode::getPosition() {
    return this->circle.getPosition();
}

void SingleNode::setText(std::string _value) {
    this->value = std::move(_value);
    this->label.setString(this->value);
    sf::FloatRect bounds = this->label.getLocalBounds();
    this->label.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    this->label.setPosition(this->circle.getPosition());
}
