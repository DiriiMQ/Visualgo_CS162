//
// Created by dirii on 04/04/2023.
//

#ifndef VISUALGO_CS162_CUSTOMTEXTBOX_HPP
#define VISUALGO_CS162_CUSTOMTEXTBOX_HPP

#include "Textbox.hpp"
#include "button.hpp"

/**
 * @brief Custom Textbox class
 */
class CustomTextbox{
private:
    sf::RenderWindow* window;
    sf::Vector2f position;
    Button* goButton;
    TextBox* textbox;
    sf::Font font;
    sf::Text title;
    std::string titleString;
    int maxLength;
    bool isGoButtonClicked;

public:
    /**
     * @brief Construct a new Custom Textbox object
     * @param window The window where the text box will be rendered
     * @param position The position of the text box
     * @param size The size of the text box
     * @param titleString The title of the text box
     * @param maxLength The maximum length of the text
     */
    CustomTextbox(sf::RenderWindow* window, sf::Vector2f position, int size, std::string titleString, int maxLength);
    ~CustomTextbox() = default;

    /**
     * @brief Poll the event
     * @details This function is used to poll the event
     * @param event The event that will be polled
     * @param mousePosView The position of the mouse
     */
    void pollEvent(sf::Event event, sf::Vector2f mousePosView);
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
    std::string getTextString();

    /**
     * @brief Reset the input
     * @details This function is used to reset the input
     */
    void resetInput();
};

#endif //VISUALGO_CS162_CUSTOMTEXTBOX_HPP
