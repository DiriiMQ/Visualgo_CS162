//
// Created by dirii on 15/04/2023.
//

#include "HIghlighter.hpp"

#include <utility>

Highlighter::Highlighter(sf::RenderWindow *window, int linesCount, const char *codePath) {
    this->window = window;
    this->linesCount = linesCount;

    this->codeTexture.loadFromFile(codePath);
    this->codeSprite.setTexture(this->codeTexture);
    this->codeSprite.setScale(constants::Highlighter::codeScale);

    this->codeSprite.setOrigin(
            this->codeSprite.getLocalBounds().width,
            this->codeSprite.getLocalBounds().height
            );

    this->codeSprite.setPosition(constants::Highlighter::codePos);

    float heightTop = 43;

    this->rectSize = sf::Vector2f(
            this->codeSprite.getGlobalBounds().width,
            ((this->codeSprite.getLocalBounds().height - heightTop * 2) / static_cast<float>(this->linesCount)) * constants::Highlighter::codeScale.y
            );

    for (int i = 0; i < this->linesCount; ++i) {
        sf::RectangleShape rect(this->rectSize);
        rect.setOrigin(rect.getLocalBounds().width, rect.getLocalBounds().height);
        rect.setFillColor(constants::transparentGreen);
        rect.setPosition(
                this->codeSprite.getPosition().x,
                this->codeSprite.getPosition().y - (heightTop * constants::Highlighter::codeScale.y) - static_cast<float>(this->linesCount - 1 - i) * this->rectSize.y
                );
        this->lines.push_back(rect);
    }
}

void Highlighter::toggle(std::vector<int> linesList) {
    this->toggleLines = std::move(linesList);
}

void Highlighter::render() {
    this->window->draw(this->codeSprite);

    for (auto &i : this->toggleLines) {
        this->window->draw(this->lines[i]);
    }
}

void Highlighter::resetToggle() {
    this->toggleLines.clear();
}
