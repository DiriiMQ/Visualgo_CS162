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

/**
 * @brief Class for menu linked list
 *
 */
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

    /**
     * @brief Init the create operator
     *
     */
    void initCreateMode();
    /**
     * @brief Poll the event for create mode
     *
     * @param event The event
     * @param mousePosView The mouse position
     */
    void pollEventCreateMode(sf::Event event, sf::Vector2f mousePosView);
    /**
     * @brief Update the create mode
     *
     */
    void updateCreateMode();
    /**
     * @brief Render the create mode
     *
     */
    void renderCreateMode();

    // stuff for add mode
    CustomTextbox* addTextbox[constants::MenuLinkedList::AddMode::TEXTBOX_COUNT];
    constants::MenuLinkedList::AddMode::Textbox activeAddMode;

    /**
     * @brief Init the add operator
     *
     */
    void initAddMode();
    /**
     * @brief Poll the event for add mode
     *
     * @param event The event
     * @param mousePosView The mouse position
     */
    void pollEventAddMode(sf::Event event, sf::Vector2f mousePosView);
    /**
     * @brief Update the add mode
     *
     */
    void updateAddMode();
    /**
     * @brief Render the add mode
     *
     */
    void renderAddMode();

    // stuff for delete mode
    CustomTextbox* deleteTextbox;

    /**
     * @brief Init the delete operator
     *
     */
    void initDeleteMode();
    /**
     * @brief Poll the event for delete mode
     *
     * @param event The event
     * @param mousePosView The mouse position
     */
    void pollEventDeleteMode(sf::Event event, sf::Vector2f mousePosView);
    /**
     * @brief Update the delete mode
     *
     */
    void updateDeleteMode();
    /**
     * @brief Render the delete mode
     *
     */
    void renderDeleteMode();

    // stuff for update mode
    CustomTextbox* updateTextbox[constants::MenuLinkedList::UpdateMode::TEXTBOX_COUNT];
    constants::MenuLinkedList::UpdateMode::Textbox activeUpdateMode;

    /**
     * @brief Init the update operator
     *
     */
    void initUpdateMode();
    /**
     * @brief Poll the event for update mode
     *
     * @param event The event
     * @param mousePosView The mouse position
     */
    void pollEventUpdateMode(sf::Event event, sf::Vector2f mousePosView);
    /**
     * @brief Update the update mode
     *
     */
    void updateUpdateMode();
    /**
     * @brief Render the update mode
     *
     */
    void renderUpdateMode();

    // stuff for search mode
    CustomTextbox* searchTextbox;

    /**
     * @brief Init the search operator
     *
     */
    void initSearchMode();
    /**
     * @brief Poll the event for search mode
     *
     * @param event The event
     * @param mousePosView The mouse position
     */
    void pollEventSearchMode(sf::Event event, sf::Vector2f mousePosView);
    /**
     * @brief Update the search mode
     *
     */
    void updateSearchMode();
    /**
     * @brief Render the search mode
     *
     */
    void renderSearchMode();

    /**
     * @brief Init the menu
     *
     */
    void init();
    /**
     * @brief Init the buttons
     *
     */
    void initButtons();

public:
    // stuff public for create mode
    std::string createModeValue[constants::MenuLinkedList::CreateMode::BUTTON_COUNT];
    /**
     * @brief Get the active create mode
     *
     * @return constants::MenuLinkedList::CreateMode::Button User's choice in create menu
     */
    constants::MenuLinkedList::CreateMode::Button getActiveCreateMode();

    // stuff public for add mode
    std::string addModeValue[constants::MenuLinkedList::AddMode::TEXTBOX_COUNT];

    // stuff public for delete mode
    std::string deleteModeValue;

    // stuff public for update mode
    std::string updateModeValue[constants::MenuLinkedList::UpdateMode::TEXTBOX_COUNT];

    // stuff public for search mode
    std::string searchModeValue;

    /**
     * @brief Construct a new Menu Linked List object
     *
     * @param window The window
     */
    explicit MenuLinkedList(sf::RenderWindow* window);
    /**
     * @brief Destroy the Menu Linked List object
     *
     */
    ~MenuLinkedList() = default;

    /**
     * @brief Reset the active option menu
     *
     */
    void resetActiveOptionMenu();

    /**
     * @brief Poll the event
     *
     * @param event The event
     * @param mousePosView The mouse position
     */
    void pollEvents(sf::Event event, sf::Vector2f mousePosView);
    /**
     * @brief Update the menu
     *
     */
    void update();
    /**
     * @brief Render the menu
     *
     */
    void render();

    /**
     * @brief Get the button in the operator menu
     *
     * @param index The index of the button
     * @return Button* The button
     */
    Button* getButton(int index);
    /**
     * @brief Get the active option menu
     *
     * @return constants::MenuLinkedList::Button The active option menu
     */
    constants::MenuLinkedList::Button getActiveOptionMenu();
};

#endif //VISUALGO_CS162_MENULINKEDLIST_HPP
