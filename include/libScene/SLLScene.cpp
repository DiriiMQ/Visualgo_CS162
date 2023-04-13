//
// Created by dirii on 26/03/2023.
//

#include "SLLScene.hpp"

void SLLScene::pollEvent(sf::Event event, sf::Vector2f mousePosView) {
    if (this->isMenuOpen)
        this->menu->pollEvents(event, mousePosView);

    this->controlMenu->pollEvents(event, mousePosView);
}

void SLLScene::update() {
    if (this->isMenuOpen)
        this->menu->update();

    this->controlMenu->update();

//    switch (this->controlMenu->getStatus()){
//        case ControlMenu::StatusCode::PREVIOUS:
//            std::cout << "PREVIOUS" << std::endl;
//            break;
//        case ControlMenu::StatusCode::PAUSE:
//            std::cout << "PAUSE" << std::endl;
//            break;
//        case ControlMenu::StatusCode::PLAY:
//            std::cout << "PLAY" << std::endl;
//            break;
//        case ControlMenu::StatusCode::NEXT:
//            std::cout << "NEXT" << std::endl;
//            break;
//        default:
//            break;
//    }

//    std::cout << "Speed: " << this->controlMenu->getSpeed() << std::endl;
}

void SLLScene::render() {
    if (this->isMenuOpen)
        this->menu->render();

    this->controlMenu->render();

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
