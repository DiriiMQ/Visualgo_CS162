//
// Created by dirii on 15/04/2023.
//

#ifndef VISUALGO_CS162_HIGHLIGHTER_HPP
#define VISUALGO_CS162_HIGHLIGHTER_HPP

#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class Highlighter {
private:
    sf::RenderWindow* window;

    sf::Texture codeTexture;
    sf::Sprite codeSprite;

    int linesCount;

    std::vector<sf::RectangleShape> lines;
    std::vector<int> toggleLines;

    sf::Vector2f rectSize;

public:
    Highlighter(sf::RenderWindow* window, int linesCount, const char* codePath);

    void toggle(std::vector<int> lines);
    void resetToggle();
    void render();
};

#endif //VISUALGO_CS162_HIGHLIGHTER_HPP
