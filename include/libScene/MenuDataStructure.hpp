//
// Created by dirii on 26/04/2023.
//

#ifndef VISUALGO_CS162_MENUDATASTRUCTURE_HPP
#define VISUALGO_CS162_MENUDATASTRUCTURE_HPP

#include <fstream>
#include "Constants.hpp"
#include "stuff/Button.hpp"
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

    void initCreateMode();
    void pollEventCreateMode(sf::Event event, sf::Vector2f mousePosView);
    void updateCreateMode();
    void renderCreateMode();

    // stuff for push mode
    CustomTextbox* pushTextbox;

    void initPushMode();
    void pollEventPushMode(sf::Event event, sf::Vector2f mousePosView);
    void updatePushMode();
    void renderPushMode();

    void init();
    void initButtons();

public:
    // stuff public for create mode
    std::string createModeValue[constants::MenuDataStructure::CreateMode::BUTTON_COUNT];
    constants::MenuDataStructure::CreateMode::Button getActiveCreateMode();

    // stuff public for push mode
    std::string pushModeValue;

    explicit MenuDataStructure(sf::RenderWindow* window);
    ~MenuDataStructure() = default;

    void resetActiveOptionMenu();
    void resetActiveOptionMenuOnly();

    void pollEvents(sf::Event event, sf::Vector2f mousePosView);
    void update();
    void render();

    Button* getButton(int index);
    constants::MenuDataStructure::Button getActiveOptionMenu();
};

#endif //VISUALGO_CS162_MENUDATASTRUCTURE_HPP
