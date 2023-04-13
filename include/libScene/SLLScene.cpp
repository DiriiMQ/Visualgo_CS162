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
    this->linkedList->render();
}

SLLScene::SLLScene(sf::RenderWindow *window) : BaseScene(window) {
    this->init();
}

void SLLScene::init() {
    this->menu = new MenuLinkedList(this->window);
    this->linkedList = new LinkedList(this->window, 10);
}

void SLLScene::reset() {
    this->menu->resetActiveOptionMenu();
}
