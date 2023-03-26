//
// Created by dirii on 23/03/2023.
//

#include "MousePosition.hpp"

void MousePosition::updateMousePosition() {
    this->mousePos = sf::Mouse::getPosition(*this->relativeWindow);
    this->mousePosView = this->relativeWindow->mapPixelToCoords(this->mousePos);
}
