//
// Created by dirii on 01/05/2023.
//

#ifndef VISUALGO_CS162_MENUARRAY_HPP
#define VISUALGO_CS162_MENUARRAY_HPP

#include <fstream>
#include "Constants.hpp"
#include "stuff/button.hpp"
#include "stuff/CustomTextbox.hpp"
#include "core/FileDialog.h"

class MenuArray {
private:
    sf::RenderWindow* window;
    Button* buttons[constants::MenuArray::BUTTON_COUNT];
    constants::MenuArray::Type typeArray;

    constants::MenuArray::Button activeOptionMenu;

    // stuff for create mode
    Button* subCreateMode[constants::MenuArray::CreateMode::BUTTON_COUNT];
    CustomTextbox* createTextbox[constants::MenuArray::CreateMode::BUTTON_COUNT];
    constants::MenuArray::CreateMode::Button activeCreateMode;
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
    CustomTextbox* addTextbox[constants::MenuArray::AddMode::TEXTBOX_COUNT];
    constants::MenuArray::AddMode::Textbox activeAddMode;

    /**
     * @brief Init the add operator
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
    CustomTextbox* updateTextbox[constants::MenuArray::UpdateMode::TEXTBOX_COUNT];
    constants::MenuArray::UpdateMode::Textbox activeUpdateMode;

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

    // stuff for allocate mode
    CustomTextbox* allocateTextbox;

    /**
     * @brief Init the allocate operator
     *
     */
    void initAllocateMode();
    /**
     * @brief Poll the event for allocate mode
     *
     * @param event The event
     * @param mousePosView The mouse position
     */
    void pollEventAllocateMode(sf::Event event, sf::Vector2f mousePosView);
    /**
     * @brief Update the allocate mode
     *
     */
    void updateAllocateMode();
    /**
     * @brief Render the allocate mode
     *
     */
    void renderAllocateMode();

    /**
     * @brief Init the menu array
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
    std::string createModeValue[constants::MenuArray::CreateMode::BUTTON_COUNT];
    /**
     * @brief Get the active create mode
     * @return constants::MenuArray::CreateMode::Button The active create mode
     */
    constants::MenuArray::CreateMode::Button getActiveCreateMode();

    // stuff public for add mode
    std::string addModeValue[constants::MenuArray::AddMode::TEXTBOX_COUNT];

    // stuff public for delete mode
    std::string deleteModeValue;

    // stuff public for update mode
    std::string updateModeValue[constants::MenuArray::UpdateMode::TEXTBOX_COUNT];

    // stuff public for search mode
    std::string searchModeValue;

    // stuff public for allocate mode
    std::string allocateModeValue;

    /**
     * @brief Construct a new Menu Array object
     *
     * @param window The window
     * @param _typeArray The type of array
     */
    explicit MenuArray(sf::RenderWindow* window, constants::MenuArray::Type _typeArray);
    /**
     * @brief Destroy the Menu Array object
     *
     */
    ~MenuArray() = default;

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
     * @brief Update the menu array
     *
     */
    void update();
    /**
     * @brief Render the menu array
     *
     */
    void render();

    /**
     * @brief Get the button
     *
     * @param index The index of button
     * @return Button* The button
     */
    Button* getButton(int index);
    /**
     * @brief Get the active option menu
     *
     * @return constants::MenuArray::Button The active option menu
     */
    constants::MenuArray::Button getActiveOptionMenu();
};

#endif //VISUALGO_CS162_MENUARRAY_HPP
