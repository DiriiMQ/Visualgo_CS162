//
// Created by dirii on 26/04/2023.
//

#ifndef VISUALGO_CS162_MENUDATASTRUCTURE_HPP
#define VISUALGO_CS162_MENUDATASTRUCTURE_HPP

#include <fstream>
#include "Constants.hpp"
#include "stuff/button.hpp"
#include "stuff/CustomTextbox.hpp"
#include "core/FileDialog.h"

class MenuDataStructure {
private:
    sf::RenderWindow* window;
    Button* buttons[constants::MenuDataStructure::BUTTON_COUNT];

    constants::MenuDataStructure::Button activeOptionMenu;

    // stuff for create mode
    Button* subCreateMode[constants::MenuDataStructure::CreateMode::BUTTON_COUNT];
    CustomTextbox* createTextbox[constants::MenuDataStructure::CreateMode::BUTTON_COUNT];
    constants::MenuDataStructure::CreateMode::Button activeCreateMode;
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

    // stuff for push mode
    CustomTextbox* pushTextbox;

    /**
     * @brief Init the push operator
     *
     */
    void initPushMode();
    /**
     * @brief Poll the event for push mode
     *
     * @param event The event
     * @param mousePosView The mouse position
     */
    void pollEventPushMode(sf::Event event, sf::Vector2f mousePosView);
    /**
     * @brief Update the push mode
     *
     */
    void updatePushMode();
    /**
     * @brief Render the push mode
     *
     */
    void renderPushMode();

    /**
     * @brief Init the menu
     */
    void init();
    /**
     * @brief Init the buttons
     */
    void initButtons();

public:
    // stuff public for create mode
    std::string createModeValue[constants::MenuDataStructure::CreateMode::BUTTON_COUNT];
    /**
     * @brief Get the active create mode
     *
     * @return constants::MenuDataStructure::CreateMode::Button The active create mode
     */
    constants::MenuDataStructure::CreateMode::Button getActiveCreateMode();

    // stuff public for push mode
    std::string pushModeValue;

    /**
     * @brief Construct a new Menu Data Structure object
     *
     * @param window The window
     */
    explicit MenuDataStructure(sf::RenderWindow* window);
    /**
     * @brief Destroy the Menu Data Structure object
     *
     */
    ~MenuDataStructure() = default;

    /**
     * @brief Reset the active option menu
     *
     */
    void resetActiveOptionMenu();
    /**
     * @brief Reset the active option menu only
     *
     */
    void resetActiveOptionMenuOnly();

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
     * @brief Get the button
     *
     * @param index The index
     * @return Button* The button
     */
    Button* getButton(int index);
    /**
     * @brief Get the active option menu
     *
     * @return constants::MenuDataStructure::Button The active option menu
     */
    constants::MenuDataStructure::Button getActiveOptionMenu();
};

#endif //VISUALGO_CS162_MENUDATASTRUCTURE_HPP
