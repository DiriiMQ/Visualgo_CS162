//
// Created by dirii on 04/04/2023.
//

#ifndef VISUALGO_CS162_CUSTOMTEXTBOX_HPP
#define VISUALGO_CS162_CUSTOMTEXTBOX_HPP

#include "Textbox.hpp"
#include "button.hpp"

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
    CustomTextbox(sf::RenderWindow* window, sf::Vector2f position, int size, std::string titleString, int maxLength);
    ~CustomTextbox() = default;

    void pollEvent(sf::Event event, sf::Vector2f mousePosView);
    void update();
    void render();

    std::string getTextString();
//    [[nodiscard]] bool checkClicked() const;
};

#endif //VISUALGO_CS162_CUSTOMTEXTBOX_HPP
