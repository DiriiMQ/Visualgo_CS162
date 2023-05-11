//
// Created by dirii on 25/03/2023.
//

#ifndef VISUALGO_CS162_BUTTON_HPP
#define VISUALGO_CS162_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"
#include "Constants.hpp"

/**
 * @brief Class for creating a button
 * @details This class is used to create a button
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
     * @details This function is used to initialize the button
     */
    void init();

public:
    /**
     * @brief Construct a new Button object
     * @details This constructor is used to create a button
     * @param window The window where the button will be rendered
     * @param position The position of the button
     * @param size The size of the button
     * @param textString The text of the button
     * @param changedTextString The text of the button when it is clicked
     * @param textSize The size of the text
     * @param textColor The color of the text
     * @param color The color of the button
     * @param hoverColor The color of the button when it is hovered
     * @param clickColor The color of the button when it is clicked
     */
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

    /**
     * @brief Poll the event
     * @details This function is used to poll the event
     * @param mousePosView
     * @return
     */
    bool pollEvent(sf::Vector2f mousePosView);
    /**
     * @brief Update the button
     * @details This function is used to update the button
     */
    void update();
    /**
     * @brief Render the button
     * @details This function is used to render the button
     */
    void render();

    /**
     * @brief Set the color
     * @details This function is used to set the color of the button
     * @param _color The color of the button
     */
    void setColor(sf::Color _color);

    /**
     * @brief Get the text string
     * @return
     */
    std::string getTextString() const;
    /**
     * @brief Get the position
     * @return
     */
    sf::Vector2f getPosition() const;
    /**
     * @brief Get the size
     * @return
     */
    sf::Vector2f getSize() const;

    /**
     * @brief Check if the button is clicked
     * @details This function is used to check if the button is clicked
     * @return True if the button is clicked, false otherwise
     */
    bool checkClicked() const;
};

#endif //VISUALGO_CS162_BUTTON_HPP
