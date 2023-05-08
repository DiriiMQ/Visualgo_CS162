//
// Created by dirii on 25/03/2023.
//

#ifndef VISUALGO_CS162_BUTTON_HPP
#define VISUALGO_CS162_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"
#include "Constants.hpp"

/**
 * @brief A class to create a button
 * 
 */
class Button{
private:
    sf::RenderWindow* window;
    sf::RoundedRectangleShape button;
    sf::Text text;
    sf::Font font;
    sf::Color color;
    sf::Color textColor;
    sf::Color hoverColor;
    sf::Color clickColor;
    sf::Vector2f position;
    sf::Vector2f size;
    int textSize;
    std::string textString;
    std::string changedTextString;
    bool isHover;
    bool isClick;

    /**
     * @brief Initialize the button
     * 
     */
    void init();

public:
    Button();
    Button(
            sf::RenderWindow* window,
            sf::Vector2f position,
            sf::Vector2f size,
            std::string textString,
            std::string changedTextString,
            int textSize,
            sf::Color textColor,
            sf::Color color,
            sf::Color hoverColor,
            sf::Color clickColor
            );

    bool pollEvent(sf::Vector2f mousePosView);
    void update();
    void render();

    void setColor(sf::Color _color);
    std::string getTextString() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

    bool checkClicked() const;
};

#endif //VISUALGO_CS162_BUTTON_HPP
