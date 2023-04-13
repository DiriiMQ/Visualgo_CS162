//
// Created by dirii on 01/04/2023.
//

#ifndef VISUALGO_CS162_TEXTBOX_HPP
#define VISUALGO_CS162_TEXTBOX_HPP

#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class TextBox {
public:
    TextBox(sf::RenderWindow* window, sf::Vector2f position, int size, sf::Color textColor, sf::Color boxColor, int maxLength);

    void pollEvent(sf::Event event);
    void update();
    void render();

    std::string getTextString() const;
    sf::RectangleShape getBox() const;
    void resetInput();

private:
    sf::RenderWindow* window;

    std::string cursor;
    sf::RectangleShape box;
    sf::Font font;
    sf::Text text;

    std::string inputString;

    int maxLength;
    sf::Color textColor;
    sf::Color boxColor;

    bool cursorVisible;
    sf::Clock flickerClock;
};

#endif //VISUALGO_CS162_TEXTBOX_HPP
