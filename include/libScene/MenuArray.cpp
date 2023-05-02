//
// Created by dirii on 01/05/2023.
//

#include "MenuArray.hpp"

MenuArray::MenuArray(sf::RenderWindow *window, constants::MenuArray::Type _typeArray) {
    this->window = window;
    this->typeArray = _typeArray;
    this->init();
}

void MenuArray::init() {
    this->initButtons();
    this->initCreateMode();
    this->initAddMode();
    this->initDeleteMode();
    this->initUpdateMode();
    this->initSearchMode();
    this->initAllocateMode();

    this->activeOptionMenu = constants::MenuArray::Button::NONE;
}

void MenuArray::initButtons() {
    for (int i = 0; i < constants::MenuArray::BUTTON_COUNT; i++) {
        sf::Vector2f position = sf::Vector2f(
                constants::sideButtonSize.x + constants::distance2ModeButtons,
                constants::submenuButtonPos.y + (constants::optionButtonSize.y + constants::distance2ModeButtons / 10) * static_cast<float>(i)
        );
        if (i == constants::MenuArray::BUTTON_COUNT - 1 && this->typeArray == constants::MenuArray::Type::STATIC)
            position = sf::Vector2f(-100, -100);
        this->buttons[i] = new Button(
                this->window,
                position,
                constants::optionButtonSize,
                constants::MenuArray::BUTTON_NAMES[i],
                constants::MenuArray::BUTTON_NAMES[i],
                constants::MenuArray::BUTTON_NAME_SIZE,
                sf::Color::Black,
                constants::normalGray,
                constants::hoverGray,
                constants::clickGray
        );
    }
}

void MenuArray::resetActiveOptionMenu() {
    this->activeOptionMenu = constants::MenuArray::Button::NONE;
    this->activeCreateMode = constants::MenuArray::CreateMode::Button::NONE;
}

void MenuArray::pollEvents(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeOptionMenu != constants::MenuArray::Button::NONE)
        this->buttons[this->activeOptionMenu]->setColor(constants::normalGray);

    for (int i = 0; i < constants::MenuArray::BUTTON_COUNT; ++i) {
        if (this->buttons[i]->pollEvent(mousePosView)) {
            std::cout << "Button " << i << " is clicked" << std::endl;
            this->activeOptionMenu = static_cast<constants::MenuArray::Button>(i);
            this->activeAddMode = constants::MenuArray::AddMode::Textbox::NONE;
        }
    }

    switch (this->activeOptionMenu) {
        case constants::MenuArray::Button::CREATE_BUTTON:
            this->pollEventCreateMode(event, mousePosView);
            break;
        case constants::MenuArray::Button::ADD_BUTTON:
            this->pollEventAddMode(event, mousePosView);
            break;
        case constants::MenuArray::Button::DELETE_BUTTON:
            this->pollEventDeleteMode(event, mousePosView);
            break;
        case constants::MenuArray::Button::UPDATE_BUTTON:
            this->pollEventUpdateMode(event, mousePosView);
            break;
        case constants::MenuArray::Button::SEARCH_BUTTON:
            this->pollEventSearchMode(event, mousePosView);
            break;
        case constants::MenuArray::Button::ALLOCATE_BUTTON:
            this->pollEventAllocateMode(event, mousePosView);
            break;
        case constants::MenuArray::Button::NONE:
            break;
    }
}

void MenuArray::update() {
    if (this->activeOptionMenu != constants::MenuArray::Button::NONE)
        this->buttons[this->activeOptionMenu]->setColor(constants::clickGreen);

    for (Button* button : this->buttons) {
        button->update();
    }

    switch (this->activeOptionMenu) {
        case constants::MenuArray::Button::CREATE_BUTTON:
            this->updateCreateMode();
            break;
        case constants::MenuArray::Button::ADD_BUTTON:
            this->updateAddMode();
            break;
        case constants::MenuArray::Button::DELETE_BUTTON:
            this->updateDeleteMode();
            break;
        case constants::MenuArray::Button::UPDATE_BUTTON:
            this->updateUpdateMode();
            break;
        case constants::MenuArray::Button::SEARCH_BUTTON:
            this->updateSearchMode();
            break;
        case constants::MenuArray::Button::ALLOCATE_BUTTON:
            this->updateAllocateMode();
            break;
        case constants::MenuArray::Button::NONE:
            break;
    }
}

void MenuArray::render() {
    for (Button* button : this->buttons) {
        button->render();
    }

    switch (this->activeOptionMenu) {
        case constants::MenuArray::Button::CREATE_BUTTON:
            this->renderCreateMode();
            break;
        case constants::MenuArray::Button::ADD_BUTTON:
            this->renderAddMode();
            break;
        case constants::MenuArray::Button::DELETE_BUTTON:
            this->renderDeleteMode();
            break;
        case constants::MenuArray::Button::UPDATE_BUTTON:
            this->renderUpdateMode();
            break;
        case constants::MenuArray::Button::SEARCH_BUTTON:
            this->renderSearchMode();
            break;
        case constants::MenuArray::Button::ALLOCATE_BUTTON:
            this->renderAllocateMode();
            break;
        case constants::MenuArray::Button::NONE:
            break;
    }
}

Button *MenuArray::getButton(int index) {
    return this->buttons[index];
}

constants::MenuArray::Button MenuArray::getActiveOptionMenu() {
    return this->activeOptionMenu;
}

constants::MenuArray::CreateMode::Button MenuArray::getActiveCreateMode() {
    return this->activeCreateMode;
}

void MenuArray::initCreateMode() {
    // init stuff for create mode
    this->activeCreateMode = constants::MenuArray::CreateMode::Button::NONE;
    for (int i = 0; i < constants::MenuArray::CreateMode::BUTTON_COUNT; i++) {
        sf::Vector2f position = sf::Vector2f(
                this->buttons[0]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons) * static_cast<float>(i + 1),
                this->buttons[0]->getPosition().y
        );
        this->subCreateMode[i] = new Button(
                this->window,
                position,
                constants::optionButtonSize,
                constants::MenuArray::CreateMode::BUTTON_NAMES[i],
                constants::MenuArray::CreateMode::BUTTON_NAMES[i],
                constants::MenuArray::CreateMode::NAME_SIZE,
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
                    constants::MenuArray::CreateMode::TEXTBOX_NAMES[i],
                    constants::MenuArray::CreateMode::TEXTBOX_LENGTH[i],
            };
        this->createModeValue[i] = "None";
    }
    this->isOpenFileDialog = false;
}
void MenuArray::pollEventCreateMode(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeCreateMode != constants::MenuArray::CreateMode::Button::NONE)
        this->subCreateMode[this->activeCreateMode]->setColor(constants::normalGray);

    for (int i = 0; i < constants::MenuArray::CreateMode::BUTTON_COUNT; i++) {
        if (this->subCreateMode[i]->pollEvent(mousePosView)) {
            this->activeCreateMode = static_cast<constants::MenuArray::CreateMode::Button>(i);
            if (i == constants::MenuArray::CreateMode::Button::FILE_BUTTON)
                this->isOpenFileDialog = true;
            std::cout << "Button " << i << " is clicked" << std::endl;
        }
    }

//    this->testTextbox->pollEvent(event);
    if (this->activeCreateMode < constants::MenuArray::CreateMode::TEXTBOX_COUNT)
        this->createTextbox[this->activeCreateMode]->pollEvent(event, mousePosView);
}
void MenuArray::updateCreateMode() {
    if (this->activeCreateMode != constants::MenuArray::CreateMode::Button::NONE)
        this->subCreateMode[this->activeCreateMode]->setColor(constants::clickGreen);

    for (Button* button : this->subCreateMode) {
        button->update();
    }

//    this->testTextbox->update();
    if (this->activeCreateMode < constants::MenuArray::CreateMode::TEXTBOX_COUNT) {
        this->createTextbox[this->activeCreateMode]->update();
        std::string inputUser = this->createTextbox[this->activeCreateMode]->getTextString();
        if (inputUser != "None") {
            std::cout << inputUser << std::endl;
            this->createTextbox[this->activeCreateMode]->resetInput();
        }
        this->createModeValue[this->activeCreateMode] = inputUser;
    } else if (this->activeCreateMode == constants::MenuArray::CreateMode::FILE_BUTTON) {
        if (this->isOpenFileDialog) {
            auto f = pfd::open_file("Choose files to read", pfd::path::home(),
                                    {"Text Files (.txt .text)", "*.txt *.text",
                                     "All Files", "*"});

            // wait for the user to select a file unless the window will be not responsive
            while (!f.ready(100)) {
                sf::Event event{};
                this->window->pollEvent(event);
            }

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
void MenuArray::renderCreateMode() {
    for (Button* button : this->subCreateMode) {
        button->render();
    }

//    this->testTextbox->render();
    if (this->activeCreateMode < constants::MenuArray::CreateMode::TEXTBOX_COUNT)
        this->createTextbox[this->activeCreateMode]->render();
}

void MenuArray::initAddMode() {
    //init stuff for add mode
    this->activeAddMode = constants::MenuArray::AddMode::Textbox::NONE;
    for (int i = 0; i < constants::MenuArray::AddMode::TEXTBOX_COUNT; i++) {
        sf::Vector2f position = sf::Vector2f(
                this->buttons[1]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons),
                this->buttons[1]->getPosition().y
        );
        this->addTextbox[i] = new CustomTextbox{
                this->window,
                position,
                20,
                constants::MenuArray::AddMode::TEXTBOX_NAMES[i],
                constants::MenuArray::AddMode::TEXTBOX_LENGTH[i],
        };
        this->addModeValue[i] = "None";
    }
}
void MenuArray::pollEventAddMode(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeAddMode == constants::MenuArray::AddMode::NONE)
        this->activeAddMode = constants::MenuArray::AddMode::POSITION_TEXTBOX;

    this->addTextbox[this->activeAddMode]->pollEvent(event, mousePosView);
}
void MenuArray::updateAddMode() {
    if (this->activeAddMode == constants::MenuArray::AddMode::NONE)
        this->activeAddMode = constants::MenuArray::AddMode::POSITION_TEXTBOX;

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
        this->activeAddMode = static_cast<constants::MenuArray::AddMode::Textbox>(!this->activeAddMode);
    }
}
void MenuArray::renderAddMode() {
    this->addTextbox[this->activeAddMode]->render();
}

void MenuArray::initDeleteMode() {
    sf::Vector2f position = sf::Vector2f(
            this->buttons[2]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons),
            this->buttons[2]->getPosition().y
    );
    this->deleteTextbox = new CustomTextbox{
            this->window,
            position,
            20,
            constants::MenuArray::DeleteMode::TEXTBOX_NAME,
            constants::MenuArray::DeleteMode::TEXTBOX_LENGTH,
    };
    this->deleteModeValue = "None";
}
void MenuArray::pollEventDeleteMode(sf::Event event, sf::Vector2f mousePosView) {
    this->deleteTextbox->pollEvent(event, mousePosView);
}
void MenuArray::updateDeleteMode() {
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
void MenuArray::renderDeleteMode() {
    this->deleteTextbox->render();
}

void MenuArray::initUpdateMode() {
    // init stuff for update mode
    this->activeUpdateMode = constants::MenuArray::UpdateMode::Textbox::NONE;
    for (int i = 0; i < constants::MenuArray::UpdateMode::TEXTBOX_COUNT; i++) {
        sf::Vector2f position = sf::Vector2f(
                this->buttons[3]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons),
                this->buttons[3]->getPosition().y
        );
        this->updateTextbox[i] = new CustomTextbox{
                this->window,
                position,
                20,
                constants::MenuArray::UpdateMode::TEXTBOX_NAMES[i],
                constants::MenuArray::UpdateMode::TEXTBOX_LENGTH[i],
        };
        this->updateModeValue[i] = "None";
    }
}
void MenuArray::pollEventUpdateMode(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeUpdateMode == constants::MenuArray::UpdateMode::NONE)
        this->activeUpdateMode = constants::MenuArray::UpdateMode::POSITION_TEXTBOX;

    this->updateTextbox[this->activeUpdateMode]->pollEvent(event, mousePosView);
}
void MenuArray::updateUpdateMode() {
    if (this->activeUpdateMode == constants::MenuArray::UpdateMode::NONE)
        this->activeUpdateMode = constants::MenuArray::UpdateMode::POSITION_TEXTBOX;

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
        this->activeUpdateMode = static_cast<constants::MenuArray::UpdateMode::Textbox>(!this->activeUpdateMode);
    }
}
void MenuArray::renderUpdateMode() {
    this->updateTextbox[this->activeUpdateMode]->render();
}

void MenuArray::initSearchMode() {
    sf::Vector2f position = sf::Vector2f(
            this->buttons[4]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons),
            this->buttons[4]->getPosition().y
    );
    this->searchTextbox = new CustomTextbox{
            this->window,
            position,
            20,
            constants::MenuArray::SearchMode::TEXTBOX_NAME,
            constants::MenuArray::SearchMode::TEXTBOX_LENGTH,
    };
    this->searchModeValue = "None";
}
void MenuArray::pollEventSearchMode(sf::Event event, sf::Vector2f mousePosView) {
    this->searchTextbox->pollEvent(event, mousePosView);
}
void MenuArray::updateSearchMode() {
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
void MenuArray::renderSearchMode() {
    this->searchTextbox->render();
}

void MenuArray::initAllocateMode() {
    sf::Vector2f position = sf::Vector2f(
            this->buttons[5]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons),
            this->buttons[5]->getPosition().y
    );
    this->allocateTextbox = new CustomTextbox{
            this->window,
            position,
            20,
            constants::MenuArray::AllocateMode::TEXTBOX_NAME,
            constants::MenuArray::AllocateMode::TEXTBOX_LENGTH,
    };
    this->allocateModeValue = "None";
}
void MenuArray::pollEventAllocateMode(sf::Event event, sf::Vector2f mousePosView) {
    this->allocateTextbox->pollEvent(event, mousePosView);
}
void MenuArray::updateAllocateMode() {
    this->allocateTextbox->update();

    std::string inputUser = this->allocateTextbox->getTextString();
    // check if input is number
    bool isValid = true;
    for (char i : inputUser)
        if (!std::isdigit(i))
            isValid = false;
    if (isValid && inputUser != "None") {
        this->allocateModeValue = inputUser;
        std::cout << inputUser << std::endl;
        this->allocateTextbox->resetInput();
    }
}
void MenuArray::renderAllocateMode() {
    this->allocateTextbox->render();
}
