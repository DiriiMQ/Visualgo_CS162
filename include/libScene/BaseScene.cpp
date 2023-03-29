//
// Created by dirii on 25/03/2023.
//

#include "BaseScene.hpp"

void BaseScene::setWindow(sf::RenderWindow *window) {
    this->window = window;
}

void BaseScene::createModeButton(sf::Vector2f position, std::string textString) {
    this->modeButton = new Button(
            this->window,
            position,
            constants::modeButtonSize,
            textString,
            textString,
            constants::sizeTextModeButton,
            sf::Color::Black,
            constants::normalGray,
            constants::hoverGray,
            constants::clickGray
            );
}

BaseScene::BaseScene(sf::RenderWindow *window) {
    this->setWindow(window);
    this->isMenuOpen = false;
    this->isDemoCodeOpen = false;
}
