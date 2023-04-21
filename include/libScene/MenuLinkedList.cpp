//
// Created by dirii on 30/03/2023.
//

#include "MenuLinkedList.hpp"

void MenuLinkedList::init() {
    this->initButtons();
    this->initCreateMode();
    this->initAddMode();
    this->initDeleteMode();
    this->initUpdateMode();
    this->initSearchMode();

    this->activeOptionMenu = constants::MenuLinkedList::Button::NONE;
}

void MenuLinkedList::initButtons() {
    for (int i = 0; i < constants::MenuLinkedList::BUTTON_COUNT; i++) {
        sf::Vector2f position = sf::Vector2f(
                constants::sideButtonSize.x + constants::distance2ModeButtons,
                constants::submenuButtonPos.y + (constants::optionButtonSize.y + constants::distance2ModeButtons / 10) * static_cast<float>(i)
                );
        this->buttons[i] = new Button(
                this->window,
                position,
                constants::optionButtonSize,
                constants::MenuLinkedList::BUTTON_NAMES[i],
                constants::MenuLinkedList::BUTTON_NAMES[i],
                constants::MenuLinkedList::BUTTON_NAME_SIZE,
                sf::Color::Black,
                constants::normalGray,
                constants::hoverGray,
                constants::clickGray
        );
    };
}

MenuLinkedList::MenuLinkedList(sf::RenderWindow *window) {
    this->window = window;
    this->init();
}

void MenuLinkedList::pollEvents(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeOptionMenu != constants::MenuLinkedList::Button::NONE)
        this->buttons[this->activeOptionMenu]->setColor(constants::normalGray);

    for (int i = 0; i < constants::MenuLinkedList::BUTTON_COUNT; i++) {
        if (this->buttons[i]->pollEvent(mousePosView)) {
            std::cout << "Button " << i << " is clicked" << std::endl;
            this->activeOptionMenu = static_cast<constants::MenuLinkedList::Button>(i);
            this->activeAddMode = constants::MenuLinkedList::AddMode::Textbox::NONE;
        }
    }

    switch (this->activeOptionMenu) {
        case constants::MenuLinkedList::Button::CREATE_BUTTON:
            this->pollEventCreateMode(event, mousePosView);
            break;
        case constants::MenuLinkedList::Button::ADD_BUTTON:
            this->pollEventAddMode(event, mousePosView);
            break;
        case constants::MenuLinkedList::Button::DELETE_BUTTON:
            this->pollEventDeleteMode(event, mousePosView);
            break;
        case constants::MenuLinkedList::Button::UPDATE_BUTTON:
            this->pollEventUpdateMode(event, mousePosView);
            break;
        case constants::MenuLinkedList::Button::SEARCH_BUTTON:
            this->pollEventSearchMode(event, mousePosView);
            break;
        case constants::MenuLinkedList::Button::NONE:
            break;
    }
}

void MenuLinkedList::update() {
    if (this->activeOptionMenu != constants::MenuLinkedList::Button::NONE)
        this->buttons[this->activeOptionMenu]->setColor(constants::clickGreen);

    for (Button* button : this->buttons) {
        button->update();
    }

    switch (this->activeOptionMenu) {
        case constants::MenuLinkedList::Button::CREATE_BUTTON:
            this->updateCreateMode();
            break;
        case constants::MenuLinkedList::Button::ADD_BUTTON:
            this->updateAddMode();
            break;
        case constants::MenuLinkedList::Button::DELETE_BUTTON:
            this->updateDeleteMode();
            break;
        case constants::MenuLinkedList::Button::UPDATE_BUTTON:
            this->updateUpdateMode();
            break;
        case constants::MenuLinkedList::Button::SEARCH_BUTTON:
            this->updateSearchMode();
            break;
        case constants::MenuLinkedList::Button::NONE:
            break;
    }
}

void MenuLinkedList::render() {
    for (Button* button : this->buttons) {
        button->render();
    }

    switch (this->activeOptionMenu) {
        case constants::MenuLinkedList::Button::CREATE_BUTTON:
            this->renderCreateMode();
            break;
        case constants::MenuLinkedList::Button::ADD_BUTTON:
            this->renderAddMode();
            break;
        case constants::MenuLinkedList::Button::DELETE_BUTTON:
            this->renderDeleteMode();
            break;
        case constants::MenuLinkedList::Button::UPDATE_BUTTON:
            this->renderUpdateMode();
            break;
        case constants::MenuLinkedList::Button::SEARCH_BUTTON:
            this->renderSearchMode();
            break;
        case constants::MenuLinkedList::Button::NONE:
            break;
    }
}

Button *MenuLinkedList::getButton(int index) {
    return this->buttons[index];
}

void MenuLinkedList::resetActiveOptionMenu() {
    this->activeOptionMenu = constants::MenuLinkedList::Button::NONE;
    this->activeCreateMode = constants::MenuLinkedList::CreateMode::Button::NONE;
}

void MenuLinkedList::initCreateMode() {
    // init stuff for create mode
    this->activeCreateMode = constants::MenuLinkedList::CreateMode::Button::NONE;
    for (int i = 0; i < constants::MenuLinkedList::CreateMode::BUTTON_COUNT; i++) {
        sf::Vector2f position = sf::Vector2f(
                this->buttons[0]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons) * static_cast<float>(i + 1),
                this->buttons[0]->getPosition().y
        );
        this->subCreateMode[i] = new Button(
                this->window,
                position,
                constants::optionButtonSize,
                constants::MenuLinkedList::CreateMode::BUTTON_NAMES[i],
                constants::MenuLinkedList::CreateMode::BUTTON_NAMES[i],
                constants::MenuLinkedList::CreateMode::NAME_SIZE,
                sf::Color::Black,
                constants::normalGray,
                constants::hoverGray,
                constants::clickGray
        );
        if (i < 2)
            this->createTextbox[i] = new CustomTextbox{
                    this->window,
                    sf::Vector2f(
                            this->subCreateMode[0]->getPosition().x,
                            this->subCreateMode[0]->getPosition().y + constants::optionButtonSize.y + constants::distance2ModeButtons
                    ),
                    20,
                    constants::MenuLinkedList::CreateMode::TEXTBOX_NAMES[i],
                    constants::MenuLinkedList::CreateMode::TEXTBOX_LENGTH[i],
            };
        this->createModeValue[i] = "None";
    }
    this->isOpenFileDialog = false;
}
void MenuLinkedList::pollEventCreateMode(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeCreateMode != constants::MenuLinkedList::CreateMode::Button::NONE)
        this->subCreateMode[this->activeCreateMode]->setColor(constants::normalGray);

    for (int i = 0; i < constants::MenuLinkedList::CreateMode::BUTTON_COUNT; i++) {
        if (this->subCreateMode[i]->pollEvent(mousePosView)) {
            this->activeCreateMode = static_cast<constants::MenuLinkedList::CreateMode::Button>(i);
            if (i == constants::MenuLinkedList::CreateMode::Button::FILE_BUTTON)
                this->isOpenFileDialog = true;
            std::cout << "Button " << i << " is clicked" << std::endl;
        }
    }

//    this->testTextbox->pollEvent(event);
    if (this->activeCreateMode < constants::MenuLinkedList::CreateMode::TEXTBOX_COUNT)
        this->createTextbox[this->activeCreateMode]->pollEvent(event, mousePosView);
}
void MenuLinkedList::updateCreateMode() {
    if (this->activeCreateMode != constants::MenuLinkedList::CreateMode::Button::NONE)
        this->subCreateMode[this->activeCreateMode]->setColor(constants::clickGreen);

    for (Button* button : this->subCreateMode) {
        button->update();
    }

//    this->testTextbox->update();
    if (this->activeCreateMode < constants::MenuLinkedList::CreateMode::TEXTBOX_COUNT) {
        this->createTextbox[this->activeCreateMode]->update();
        std::string inputUser = this->createTextbox[this->activeCreateMode]->getTextString();
        if (inputUser != "None") {
            std::cout << inputUser << std::endl;
            this->createTextbox[this->activeCreateMode]->resetInput();
        }
        this->createModeValue[this->activeCreateMode] = inputUser;
    } else if (this->activeCreateMode == constants::MenuLinkedList::CreateMode::FILE_BUTTON) {
        if (this->isOpenFileDialog) {
            auto f = pfd::open_file("Choose files to read", pfd::path::home(),
                                    {"Text Files (.txt .text)", "*.txt *.text",
                                     "All Files", "*"});
            if (!f.result().empty()) {
                std::ifstream file(f.result()[0]);
                std::string line;
                file >> line;
                this->createModeValue[this->activeCreateMode] = line;
            }
        }
        this->isOpenFileDialog = false;
    }
}
void MenuLinkedList::renderCreateMode() {
    for (Button* button : this->subCreateMode) {
        button->render();
    }

//    this->testTextbox->render();
    if (this->activeCreateMode < constants::MenuLinkedList::CreateMode::TEXTBOX_COUNT)
        this->createTextbox[this->activeCreateMode]->render();
}

constants::MenuLinkedList::CreateMode::Button MenuLinkedList::getActiveCreateMode() {
    return this->activeCreateMode;
}

constants::MenuLinkedList::Button MenuLinkedList::getActiveOptionMenu() {
    return this->activeOptionMenu;
}

void MenuLinkedList::initAddMode() {
    //init stuff for add mode
    this->activeAddMode = constants::MenuLinkedList::AddMode::Textbox::NONE;
    for (int i = 0; i < constants::MenuLinkedList::AddMode::TEXTBOX_COUNT; i++) {
        sf::Vector2f position = sf::Vector2f(
                this->buttons[1]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons),
                this->buttons[1]->getPosition().y
        );
        this->addTextbox[i] = new CustomTextbox{
                this->window,
                position,
                20,
                constants::MenuLinkedList::AddMode::TEXTBOX_NAMES[i],
                constants::MenuLinkedList::AddMode::TEXTBOX_LENGTH[i],
        };
        this->addModeValue[i] = "None";
    }
}
void MenuLinkedList::pollEventAddMode(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeAddMode == constants::MenuLinkedList::AddMode::NONE)
        this->activeAddMode = constants::MenuLinkedList::AddMode::POSITION_TEXTBOX;

    this->addTextbox[this->activeAddMode]->pollEvent(event, mousePosView);
}
void MenuLinkedList::updateAddMode() {
    if (this->activeAddMode == constants::MenuLinkedList::AddMode::NONE)
        this->activeAddMode = constants::MenuLinkedList::AddMode::POSITION_TEXTBOX;

    this->addTextbox[this->activeAddMode]->update();

    std::string inputUser = this->addTextbox[this->activeAddMode]->getTextString();
    // check if input is number
    bool isValid = true;
    for (char i : inputUser)
        if (!std::isdigit(i))
            isValid = false;
    if (isValid && inputUser != "None") {
        this->addModeValue[this->activeAddMode] = inputUser;
        std::cout << inputUser << std::endl;
        this->addTextbox[this->activeAddMode]->resetInput();
        this->activeAddMode = static_cast<constants::MenuLinkedList::AddMode::Textbox>(!this->activeAddMode);
    }
}
void MenuLinkedList::renderAddMode() {
    this->addTextbox[this->activeAddMode]->render();
}

void MenuLinkedList::initDeleteMode() {
    sf::Vector2f position = sf::Vector2f(
            this->buttons[2]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons),
            this->buttons[2]->getPosition().y
    );
    this->deleteTextbox = new CustomTextbox{
            this->window,
            position,
            20,
            constants::MenuLinkedList::DeleteMode::TEXTBOX_NAME,
            constants::MenuLinkedList::DeleteMode::TEXTBOX_LENGTH,
    };
    this->deleteModeValue = "None";
}
void MenuLinkedList::pollEventDeleteMode(sf::Event event, sf::Vector2f mousePosView) {
    this->deleteTextbox->pollEvent(event, mousePosView);
}
void MenuLinkedList::updateDeleteMode() {
    this->deleteTextbox->update();

    std::string inputUser = this->deleteTextbox->getTextString();
    // check if input is number
    bool isValid = true;
    for (char i : inputUser)
        if (!std::isdigit(i))
            isValid = false;
    if (isValid && inputUser != "None") {
        this->deleteModeValue = inputUser;
        std::cout << inputUser << std::endl;
        this->deleteTextbox->resetInput();
    }
}
void MenuLinkedList::renderDeleteMode() {
    this->deleteTextbox->render();
}

void MenuLinkedList::initUpdateMode() {
    // init stuff for update mode
    this->activeUpdateMode = constants::MenuLinkedList::UpdateMode::Textbox::NONE;
    for (int i = 0; i < constants::MenuLinkedList::UpdateMode::TEXTBOX_COUNT; i++) {
        sf::Vector2f position = sf::Vector2f(
                this->buttons[3]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons),
                this->buttons[3]->getPosition().y
        );
        this->updateTextbox[i] = new CustomTextbox{
                this->window,
                position,
                20,
                constants::MenuLinkedList::UpdateMode::TEXTBOX_NAMES[i],
                constants::MenuLinkedList::UpdateMode::TEXTBOX_LENGTH[i],
        };
        this->updateModeValue[i] = "None";
    }
}
void MenuLinkedList::pollEventUpdateMode(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeUpdateMode == constants::MenuLinkedList::UpdateMode::NONE)
        this->activeUpdateMode = constants::MenuLinkedList::UpdateMode::POSITION_TEXTBOX;

    this->updateTextbox[this->activeUpdateMode]->pollEvent(event, mousePosView);
}
void MenuLinkedList::updateUpdateMode() {
    if (this->activeUpdateMode == constants::MenuLinkedList::UpdateMode::NONE)
        this->activeUpdateMode = constants::MenuLinkedList::UpdateMode::POSITION_TEXTBOX;

    this->updateTextbox[this->activeUpdateMode]->update();

    std::string inputUser = this->updateTextbox[this->activeUpdateMode]->getTextString();
    // check if input is number
    bool isValid = true;
    for (char i : inputUser)
        if (!std::isdigit(i))
            isValid = false;
    if (isValid && inputUser != "None") {
        this->updateModeValue[this->activeUpdateMode] = inputUser;
        std::cout << inputUser << std::endl;
        this->updateTextbox[this->activeUpdateMode]->resetInput();
        this->activeUpdateMode = static_cast<constants::MenuLinkedList::UpdateMode::Textbox>(!this->activeUpdateMode);
    }
}
void MenuLinkedList::renderUpdateMode() {
    this->updateTextbox[this->activeUpdateMode]->render();
}

void MenuLinkedList::initSearchMode() {
    sf::Vector2f position = sf::Vector2f(
            this->buttons[4]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons),
            this->buttons[4]->getPosition().y
    );
    this->searchTextbox = new CustomTextbox{
            this->window,
            position,
            20,
            constants::MenuLinkedList::SearchMode::TEXTBOX_NAME,
            constants::MenuLinkedList::SearchMode::TEXTBOX_LENGTH,
    };
    this->searchModeValue = "None";
}

void MenuLinkedList::pollEventSearchMode(sf::Event event, sf::Vector2f mousePosView) {
    this->searchTextbox->pollEvent(event, mousePosView);
}

void MenuLinkedList::updateSearchMode() {
    this->searchTextbox->update();

    std::string inputUser = this->searchTextbox->getTextString();
    // check if input is number
    bool isValid = true;
    for (char i : inputUser)
        if (!std::isdigit(i))
            isValid = false;
    if (isValid && inputUser != "None") {
        this->searchModeValue = inputUser;
        std::cout << inputUser << std::endl;
        this->searchTextbox->resetInput();
    }
}

void MenuLinkedList::renderSearchMode() {
    this->searchTextbox->render();
}
