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

    void initCreateMode();
    void pollEventCreateMode(sf::Event event, sf::Vector2f mousePosView);
    void updateCreateMode();
    void renderCreateMode();

    // stuff for add mode
    CustomTextbox* addTextbox[constants::MenuArray::AddMode::TEXTBOX_COUNT];
    constants::MenuArray::AddMode::Textbox activeAddMode;

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
    CustomTextbox* updateTextbox[constants::MenuArray::UpdateMode::TEXTBOX_COUNT];
    constants::MenuArray::UpdateMode::Textbox activeUpdateMode;

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

    // stuff for allocate mode
    CustomTextbox* allocateTextbox;

    void initAllocateMode();
    void pollEventAllocateMode(sf::Event event, sf::Vector2f mousePosView);
    void updateAllocateMode();
    void renderAllocateMode();

    void init();
    void initButtons();

public:
    // stuff public for create mode
    std::string createModeValue[constants::MenuArray::CreateMode::BUTTON_COUNT];
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

    explicit MenuArray(sf::RenderWindow* window, constants::MenuArray::Type _typeArray);
    ~MenuArray() = default;

    void resetActiveOptionMenu();

    void pollEvents(sf::Event event, sf::Vector2f mousePosView);
    void update();
    void render();

    Button* getButton(int index);
    constants::MenuArray::Button getActiveOptionMenu();
};

#endif //VISUALGO_CS162_MENUARRAY_HPP
