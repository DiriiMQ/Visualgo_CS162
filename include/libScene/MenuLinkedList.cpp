//
// Created by dirii on 30/03/2023.
//

#include "MenuLinkedList.hpp"

void MenuLinkedList::init() {
    this->initButtons();

    this->activeOptionMenu = constants::MenuLinkedList::Button::NONE;
    this->activeCreateMode = constants::MenuLinkedList::CreateMode::Button::NONE;
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

    // init stuff for create mode
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
    }
}

MenuLinkedList::MenuLinkedList(sf::RenderWindow *window) {
    this->window = window;
    this->init();

//    this->testTextbox = new TextBox(
//            this->window,
//            sf::Vector2f(200, 200),
//            20,
//            sf::Color::Black,
//            sf::Color::White,
//            30
//    );
}

void MenuLinkedList::pollEvents(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeOptionMenu != constants::MenuLinkedList::Button::NONE)
        this->buttons[this->activeOptionMenu]->setColor(constants::normalGray);

    for (int i = 0; i < constants::MenuLinkedList::BUTTON_COUNT; i++) {
        if (this->buttons[i]->pollEvent(mousePosView)) {
            std::cout << "Button " << i << " is clicked" << std::endl;
            this->activeOptionMenu = static_cast<constants::MenuLinkedList::Button>(i);
        }
    }

    switch (this->activeOptionMenu) {
        case constants::MenuLinkedList::Button::CREATE_BUTTON:
            this->pollEventCreateMode(event, mousePosView);
            break;
        case constants::MenuLinkedList::Button::ADD_BUTTON:
            break;
        case constants::MenuLinkedList::Button::DELETE_BUTTON:
            break;
        case constants::MenuLinkedList::Button::SEARCH_BUTTON:
            break;
        case constants::MenuLinkedList::Button::UPDATE_BUTTON:
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
            break;
        case constants::MenuLinkedList::Button::DELETE_BUTTON:
            break;
        case constants::MenuLinkedList::Button::SEARCH_BUTTON:
            break;
        case constants::MenuLinkedList::Button::UPDATE_BUTTON:
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
            break;
        case constants::MenuLinkedList::Button::DELETE_BUTTON:
            break;
        case constants::MenuLinkedList::Button::SEARCH_BUTTON:
            break;
        case constants::MenuLinkedList::Button::UPDATE_BUTTON:
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

void MenuLinkedList::pollEventCreateMode(sf::Event event, sf::Vector2f mousePosView) {
    if (this->activeCreateMode != constants::MenuLinkedList::CreateMode::Button::NONE)
        this->subCreateMode[this->activeCreateMode]->setColor(constants::normalGray);

    for (int i = 0; i < constants::MenuLinkedList::CreateMode::BUTTON_COUNT; i++) {
        if (this->subCreateMode[i]->pollEvent(mousePosView)) {
            this->activeCreateMode = static_cast<constants::MenuLinkedList::CreateMode::Button>(i);
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
        if (inputUser != "None")
            std::cout << inputUser << std::endl;
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
