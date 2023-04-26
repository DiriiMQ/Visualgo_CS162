//
// Created by dirii on 26/04/2023.
//

#include "MenuDataStructure.hpp"

MenuDataStructure::MenuDataStructure(sf::RenderWindow *window) {
    this->window = window;
    this->init();
}

void MenuDataStructure::init() {
    this->initButtons();
    this->initCreateMode();
    this->initPushMode();

    this->activeOptionMenu = constants::MenuDataStructure::Button::NONE;
}

void MenuDataStructure::initButtons() {
    for (int i = 0; i < constants::MenuDataStructure::BUTTON_COUNT; i++) {
        sf::Vector2f position = sf::Vector2f(
                constants::sideButtonSize.x + constants::distance2ModeButtons,
                constants::submenuButtonPos.y + (constants::optionButtonSize.y + constants::distance2ModeButtons / 10) * static_cast<float>(i)
        );
        this->buttons[i] = new Button(
                this->window,
                position,
                constants::optionButtonSize,
                constants::MenuDataStructure::BUTTON_NAMES[i],
                constants::MenuDataStructure::BUTTON_NAMES[i],
                constants::MenuDataStructure::BUTTON_NAME_SIZE,
                sf::Color::Black,
                constants::normalGray,
                constants::hoverGray,
                constants::clickGray
        );
    }
}

void MenuDataStructure::pollEvents(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeOptionMenu != constants::MenuDataStructure::Button::NONE)
        this->buttons[this->activeOptionMenu]->setColor(constants::normalGray);

    for (int i = 0; i < constants::MenuDataStructure::BUTTON_COUNT; i++) {
        if (this->buttons[i]->pollEvent(mousePosView)) {
            std::cout << "Button " << i << " is clicked" << std::endl;
            this->activeOptionMenu = static_cast<constants::MenuDataStructure::Button>(i);
        }
    }

    if (this->activeOptionMenu == constants::MenuDataStructure::Button::CREATE_BUTTON) {
        this->pollEventCreateMode(event, mousePosView);
    } else if (this->activeOptionMenu == constants::MenuDataStructure::Button::PUSH_BUTTON) {
        this->pollEventPushMode(event, mousePosView);
    }
}

void MenuDataStructure::update() {
    if (this->activeOptionMenu < constants::MenuDataStructure::Button::POP_BUTTON)
        this->buttons[this->activeOptionMenu]->setColor(constants::clickGreen);

    for (Button* button : this->buttons) {
        button->update();
    }
    
    if (this->activeOptionMenu == constants::MenuDataStructure::Button::CREATE_BUTTON) {
        this->updateCreateMode();
    } else if (this->activeOptionMenu == constants::MenuDataStructure::Button::PUSH_BUTTON) {
        this->updatePushMode();
    }
}

void MenuDataStructure::render() {
    for (Button* button : this->buttons) {
        button->render();
    }
    
    if (this->activeOptionMenu == constants::MenuDataStructure::Button::CREATE_BUTTON) {
        this->renderCreateMode();
    } else if (this->activeOptionMenu == constants::MenuDataStructure::Button::PUSH_BUTTON) {
        this->renderPushMode();
    }
}

Button *MenuDataStructure::getButton(int index) {
    return this->buttons[index];
}

constants::MenuDataStructure::Button MenuDataStructure::getActiveOptionMenu() {
    return this->activeOptionMenu;
}

constants::MenuDataStructure::CreateMode::Button MenuDataStructure::getActiveCreateMode() {
    return this->activeCreateMode;
}

void MenuDataStructure::initCreateMode() {
// init stuff for create mode
    this->activeCreateMode = constants::MenuDataStructure::CreateMode::Button::NONE;
    for (int i = 0; i < constants::MenuDataStructure::CreateMode::BUTTON_COUNT; i++) {
        sf::Vector2f position = sf::Vector2f(
                this->buttons[0]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons) * static_cast<float>(i + 1),
                this->buttons[0]->getPosition().y
        );
        this->subCreateMode[i] = new Button(
                this->window,
                position,
                constants::optionButtonSize,
                constants::MenuDataStructure::CreateMode::BUTTON_NAMES[i],
                constants::MenuDataStructure::CreateMode::BUTTON_NAMES[i],
                constants::MenuDataStructure::CreateMode::NAME_SIZE,
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
                    constants::MenuDataStructure::CreateMode::TEXTBOX_NAMES[i],
                    constants::MenuDataStructure::CreateMode::TEXTBOX_LENGTH[i],
            };
        this->createModeValue[i] = "None";
    }
    this->isOpenFileDialog = false;
}

void MenuDataStructure::pollEventCreateMode(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeCreateMode != constants::MenuDataStructure::CreateMode::Button::NONE)
        this->subCreateMode[this->activeCreateMode]->setColor(constants::normalGray);

    for (int i = 0; i < constants::MenuDataStructure::CreateMode::BUTTON_COUNT; i++) {
        if (this->subCreateMode[i]->pollEvent(mousePosView)) {
            this->activeCreateMode = static_cast<constants::MenuDataStructure::CreateMode::Button>(i);
            if (i == constants::MenuDataStructure::CreateMode::Button::FILE_BUTTON)
                this->isOpenFileDialog = true;
            std::cout << "Button " << i << " is clicked" << std::endl;
        }
    }

    if (this->activeCreateMode < constants::MenuDataStructure::CreateMode::TEXTBOX_COUNT)
        this->createTextbox[this->activeCreateMode]->pollEvent(event, mousePosView);
}

void MenuDataStructure::updateCreateMode() {
    if (this->activeCreateMode != constants::MenuDataStructure::CreateMode::Button::NONE)
        this->subCreateMode[this->activeCreateMode]->setColor(constants::clickGreen);

    for (Button* button : this->subCreateMode) {
        button->update();
    }

//    this->testTextbox->update();
    if (this->activeCreateMode < constants::MenuDataStructure::CreateMode::TEXTBOX_COUNT) {
        this->createTextbox[this->activeCreateMode]->update();
        std::string inputUser = this->createTextbox[this->activeCreateMode]->getTextString();
        if (inputUser != "None") {
            std::cout << inputUser << std::endl;
            this->createTextbox[this->activeCreateMode]->resetInput();
        }
        this->createModeValue[this->activeCreateMode] = inputUser;
    } else if (this->activeCreateMode == constants::MenuDataStructure::CreateMode::FILE_BUTTON) {
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

void MenuDataStructure::renderCreateMode() {
    for (Button* button : this->subCreateMode) {
        button->render();
    }

    if (this->activeCreateMode < constants::MenuDataStructure::CreateMode::TEXTBOX_COUNT)
        this->createTextbox[this->activeCreateMode]->render();
}

void MenuDataStructure::initPushMode() {
    sf::Vector2f position = sf::Vector2f(
            this->buttons[1]->getPosition().x + (constants::optionButtonSize.x + constants::distance2ModeButtons),
            this->buttons[1]->getPosition().y
    );
    this->pushTextbox = new CustomTextbox{
            this->window,
            position,
            20,
            constants::MenuDataStructure::PushMode::TEXTBOX_NAME,
            constants::MenuDataStructure::PushMode::TEXTBOX_LENGTH,
    };
    this->pushModeValue = "None";
}

void MenuDataStructure::pollEventPushMode(sf::Event event, sf::Vector2f mousePosView) {
    this->pushTextbox->pollEvent(event, mousePosView);
}

void MenuDataStructure::updatePushMode() {
    this->pushTextbox->update();

    std::string inputUser = this->pushTextbox->getTextString();
    // check if input is number
    bool isValid = true;
    for (char i : inputUser)
        if (!std::isdigit(i))
            isValid = false;
    if (isValid && inputUser != "None") {
        this->pushModeValue = inputUser;
        std::cout << inputUser << std::endl;
        this->pushTextbox->resetInput();
    }
}

void MenuDataStructure::renderPushMode() {
    this->pushTextbox->render();
}

void MenuDataStructure::resetActiveOptionMenu() {
    this->activeOptionMenu = constants::MenuDataStructure::Button::NONE;
    this->activeCreateMode = constants::MenuDataStructure::CreateMode::Button::NONE;
}

void MenuDataStructure::resetActiveOptionMenuOnly(){
    this->activeOptionMenu = constants::MenuDataStructure::Button::NONE;
}