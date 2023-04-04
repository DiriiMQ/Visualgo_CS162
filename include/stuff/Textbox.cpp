//
// Created by dirii on 01/04/2023.
//

#include "Textbox.hpp"

TextBox::TextBox(sf::RenderWindow* window, sf::Vector2f position, int size, sf::Color textColor,
                 sf::Color boxColor, int maxLength) {
    this->window = window;

    this->cursor = "|";

    this->box.setPosition(position);
    this->box.setSize(sf::Vector2f(static_cast<float>((maxLength + 1) * 11), static_cast<float>(size * 1.5)));
    this->box.setFillColor(boxColor);
    this->box.setOutlineColor(sf::Color::Black);
    this->box.setOutlineThickness(1);

    font.loadFromFile(constants::fontPath);
    this->text.setFont(font);
    this->text.setCharacterSize(size);
    this->text.setFillColor(textColor);
    this->text.setPosition(position);

    this->maxLength = maxLength;
    this->textColor = textColor;
    this->boxColor = boxColor;

    this->cursorVisible = true;
    this->flickerClock.restart();
}

void TextBox::pollEvent(sf::Event event) {
    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode == '\b')
        {
            if (!inputString.empty())
            {
                inputString.pop_back();
            }
        }
        else if (((48 <= event.text.unicode && event.text.unicode <= 57) || event.text.unicode == static_cast<int>(',')) && inputString.size() < maxLength)
        {
            inputString += static_cast<char>(event.text.unicode);
//            std::cout << inputString << std::endl;
        }

        text.setString(inputString);
    }

//    std::cout << inputString << std::endl;
//    if (event.type == sf::Event::Resized)
//    {
//        box.setPosition(
//                static_cast<float>(this->window->getSize().x) / 2 - box.getSize().x / 2,
//                static_cast<float>(this->window->getSize().y) / 2 - box.getSize().y / 2
//                );
//        text.setPosition(box.getPosition().x + 10, box.getPosition().y);
//        cursor.setPosition(text.getGlobalBounds().width + text.getPosition().x, cursor.getPosition().y);
//    }
}

void TextBox::update() {
    if (flickerClock.getElapsedTime().asSeconds() >= 0.5)
    {
        cursorVisible = !cursorVisible;
        flickerClock.restart();
    }

    if (cursorVisible)
    {
        text.setString(inputString + cursor);
    }
    else
    {
        text.setString(inputString);
    }
}

void TextBox::render() {
    this->window->draw(box);
    this->window->draw(this->text);
}

std::string TextBox::getTextString() const {
    return this->inputString;
}

sf::RectangleShape TextBox::getBox() const {
    return this->box;
}
