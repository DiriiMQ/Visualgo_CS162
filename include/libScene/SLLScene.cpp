//
// Created by dirii on 26/03/2023.
//

#include "SLLScene.hpp"

void SLLScene::pollEvent(sf::Event event, sf::Vector2f mousePosView) {
    if (this->isMenuOpen)
        this->menu->pollEvents(event, mousePosView);
}

void SLLScene::update() {
    if (this->isMenuOpen)
        this->menu->update();
}

void SLLScene::render() {
    if (this->isMenuOpen)
        this->menu->render();

//    this->window->draw(*this->text);
}

SLLScene::SLLScene(sf::RenderWindow *window) : BaseScene(window) {
    this->init();
}

void SLLScene::init() {
//    this->font = new sf::Font();
//    this->font->loadFromFile(constants::fontPath);
//    this->text = new sf::Text("SLL", *this->font, 30);
//    this->text->setFillColor(sf::Color::Black);
//    this->text->setPosition(100, 100);

    this->menu = new MenuLinkedList(this->window);
}

void SLLScene::reset() {
    this->menu->resetActiveOptionMenu();
}


