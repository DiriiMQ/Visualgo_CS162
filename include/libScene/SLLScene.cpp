//
// Created by dirii on 26/03/2023.
//

#include "SLLScene.hpp"

void SLLScene::update() {

}

void SLLScene::render() {
    this->window->draw(*this->text);
}

SLLScene::SLLScene(sf::RenderWindow *window) : BaseScene(window) {
    this->init();
}

void SLLScene::pollEvent(sf::Vector2f mousePosView) {

}

void SLLScene::init() {
    this->font = new sf::Font();
    this->font->loadFromFile(constants::fontPath);
    this->text = new sf::Text("SLL", *this->font, 30);
    this->text->setFillColor(sf::Color::Black);
    this->text->setPosition(100, 100);
}
