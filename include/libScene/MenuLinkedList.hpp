//
// Created by dirii on 30/03/2023.
//

#ifndef VISUALGO_CS162_MENULINKEDLIST_HPP
#define VISUALGO_CS162_MENULINKEDLIST_HPP

#include <SFML/Graphics.hpp>
#include "stuff/button.hpp"
#include "stuff/CustomTextbox.hpp"
#include "Constants.hpp"
#include <iostream>

class MenuLinkedList {
protected:
    sf::RenderWindow* window;
    Button* buttons[constants::MenuLinkedList::BUTTON_COUNT];

    constants::MenuLinkedList::Button activeOptionMenu;

    // stuff for create mode
    Button* subCreateMode[constants::MenuLinkedList::CreateMode::BUTTON_COUNT];
    CustomTextbox* createTextbox[constants::MenuLinkedList::CreateMode::BUTTON_COUNT];
    constants::MenuLinkedList::CreateMode::Button activeCreateMode;

    void pollEventCreateMode(sf::Event event, sf::Vector2f mousePosView);
    void updateCreateMode();
    void renderCreateMode();

    void init();
    void initButtons();

public:
    explicit MenuLinkedList(sf::RenderWindow* window);
    ~MenuLinkedList() = default;

    void resetActiveOptionMenu();

    void pollEvents(sf::Event event, sf::Vector2f mousePosView);
    void update();
    void render();

    Button* getButton(int index);
};

#endif //VISUALGO_CS162_MENULINKEDLIST_HPP
