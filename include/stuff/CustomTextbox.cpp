//
// Created by dirii on 04/04/2023.
//

#include "CustomTextbox.hpp"

CustomTextbox::CustomTextbox(sf::RenderWindow *window, sf::Vector2f position, int size,
                             std::string _titleString, int maxLength) {
    this->window = window;
    this->titleString = std::move(_titleString);
    this->position = position;

    font.loadFromFile(constants::fontPath);
    this->title.setFont(font);
    this->title.setCharacterSize(size);
    this->title.setFillColor(sf::Color::Black);
    this->title.setString(this->titleString);
    this->title.setPosition(this->position);

    float width = this->title.findCharacterPos(this->titleString.size() - 1).x - this->title.findCharacterPos(0).x;

//    std::cout << width << ' ' << this->title.getString().getSize() << std::endl;

    this->maxLength = maxLength;

    this->textbox = new TextBox(
        this->window,
        sf::Vector2f(this->position.x + width + 10, this->position.y),
        20,
        sf::Color::Black,
        sf::Color::White,
        this->maxLength
        );

    this->goButton = new Button(
        this->window,
        sf::Vector2f(this->textbox->getBox().getPosition().x + this->textbox->getBox().getSize().x + 10, this->position.y),
        constants::goButtonSize,
        "Go",
        "Go",
        20,
        sf::Color::Black,
        constants::normalGray,
        constants::hoverGray,
        constants::clickGray
        );

    this->isGoButtonClicked = false;
}

void CustomTextbox::pollEvent(sf::Event event, sf::Vector2f mousePosView) {
    this->textbox->pollEvent(event);
    if (this->goButton->pollEvent(mousePosView)) {
        this->isGoButtonClicked = true;
//        std::cout << "Go button clicked!\n";
    }
}

void CustomTextbox::update() {
    this->textbox->update();
    this->goButton->update();
}

void CustomTextbox::render() {
    this->window->draw(this->title);
    this->textbox->render();
    this->goButton->render();
}

std::string CustomTextbox::getTextString(){
    if (this->isGoButtonClicked) {
        this->isGoButtonClicked = false;
        return this->textbox->getTextString();
    }
    return "None";
}

//bool CustomTextbox::checkClicked() const{
//    return false;
//}
