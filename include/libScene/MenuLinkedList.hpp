//
// Created by dirii on 30/03/2023.
//

#ifndef VISUALGO_CS162_MENULINKEDLIST_HPP
#define VISUALGO_CS162_MENULINKEDLIST_HPP

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "core/FileDialog.h"
#include "stuff/button.hpp"
#include "stuff/CustomTextbox.hpp"
#include "Constants.hpp"

class MenuLinkedList {
protected:
    sf::RenderWindow* window;
    Button* buttons[constants::MenuLinkedList::BUTTON_COUNT];

    constants::MenuLinkedList::Button activeOptionMenu;

    // stuff for create mode
    Button* subCreateMode[constants::MenuLinkedList::CreateMode::BUTTON_COUNT];
    CustomTextbox* createTextbox[constants::MenuLinkedList::CreateMode::BUTTON_COUNT];
    constants::MenuLinkedList::CreateMode::Button activeCreateMode;
    bool isOpenFileDialog = false;

    void initCreateMode();
    void pollEventCreateMode(sf::Event event, sf::Vector2f mousePosView);
    void updateCreateMode();
    void renderCreateMode();

    // stuff for add mode
    CustomTextbox* addTextbox[constants::MenuLinkedList::AddMode::TEXTBOX_COUNT];
    constants::MenuLinkedList::AddMode::Textbox activeAddMode;

    void initAddMode();
    void pollEventAddMode(sf::Event event, sf::Vector2f mousePosView);
    void updateAddMode();
    void renderAddMode();

    // stuff for delete mode
    CustomTextbox* deleteTextbox;

    void initDeleteMode();
    void pollEventDeleteMode(sf::Event event, sf::Vector2f mousePosView);
    void updateDeleteMode();
    void renderDeleteMode();

    // stuff for update mode
    CustomTextbox* updateTextbox[constants::MenuLinkedList::UpdateMode::TEXTBOX_COUNT];
    constants::MenuLinkedList::UpdateMode::Textbox activeUpdateMode;

    void initUpdateMode();
    void pollEventUpdateMode(sf::Event event, sf::Vector2f mousePosView);
    void updateUpdateMode();
    void renderUpdateMode();

    // stuff for search mode
    CustomTextbox* searchTextbox;

    void initSearchMode();
    void pollEventSearchMode(sf::Event event, sf::Vector2f mousePosView);
    void updateSearchMode();
    void renderSearchMode();

    void init();
    void initButtons();

public:
    // stuff public for create mode
    std::string createModeValue[constants::MenuLinkedList::CreateMode::BUTTON_COUNT];
    constants::MenuLinkedList::CreateMode::Button getActiveCreateMode();

    // stuff public for add mode
    std::string addModeValue[constants::MenuLinkedList::AddMode::TEXTBOX_COUNT];

    // stuff public for delete mode
    std::string deleteModeValue;

    // stuff public for update mode
    std::string updateModeValue[constants::MenuLinkedList::UpdateMode::TEXTBOX_COUNT];

    // stuff public for search mode
    std::string searchModeValue;

    explicit MenuLinkedList(sf::RenderWindow* window);
    ~MenuLinkedList() = default;

    void resetActiveOptionMenu();

    void pollEvents(sf::Event event, sf::Vector2f mousePosView);
    void update();
    void render();

    Button* getButton(int index);
    constants::MenuLinkedList::Button getActiveOptionMenu();
};

#endif //VISUALGO_CS162_MENULINKEDLIST_HPP
