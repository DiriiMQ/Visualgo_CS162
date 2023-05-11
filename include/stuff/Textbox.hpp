//
// Created by dirii on 01/04/2023.
//

#ifndef VISUALGO_CS162_TEXTBOX_HPP
#define VISUALGO_CS162_TEXTBOX_HPP

#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

/**
 * @brief Class for creating a text box
 * @details This class is used to create a text box that can be used to get input from the user
 */
class TextBox {
public:
    /**
     * @brief Construct a new Text Box object
     * @details This constructor is used to create a text box
     * @param window The window where the text box will be rendered
     * @param position The position of the text box
     * @param size The size of the text box
     * @param textColor The color of the text
     * @param boxColor The color of the box
     * @param maxLength The maximum length of the text
     */
    TextBox(sf::RenderWindow* window, sf::Vector2f position, int size, sf::Color textColor, sf::Color boxColor, int maxLength);

    /**
     * @brief Poll the event
     * @details This function is used to poll the event
     * @param event The event that will be polled
     */
    void pollEvent(sf::Event event);
    /**
     * @brief Update the text box
     * @details This function is used to update the text box
     */
    void update();
    /**
     * @brief Render the text box
     * @details This function is used to render the text box
     */
    void render();

    /**
     * @brief Get the input string
     * @details This function is used to get the input string
     * @return The input string
     */
    std::string getTextString() const;
    /**
     * @brief Get the box
     * @details This function is used to get the box
     * @return The box
     */
    sf::RectangleShape getBox() const;
    /**
     * @brief Get the text
     * @details This function is used to get the text
     * @return The text
     */
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
