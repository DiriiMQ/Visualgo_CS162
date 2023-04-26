//
// Created by dirii on 28/03/2023.
//

#include "StackScene.hpp"

StackScene::StackScene(sf::RenderWindow *window) : BaseScene(window) {
    this->init();
}

void StackScene::update() {
    if (this->isMenuOpen) {
        this->menu->update();

        constants::MenuDataStructure::Button status = this->menu->getActiveOptionMenu();
        constants::MenuDataStructure::CreateMode::Button createMode;
        switch (status) {
            case constants::MenuDataStructure::Button::CREATE_BUTTON:
                createMode = this->menu->getActiveCreateMode();
                if (createMode == constants::MenuDataStructure::CreateMode::Button::RANDOM_BUTTON) {
                    if (this->menu->createModeValue[0] == "None")
                        break;
                    if (this->menu->createModeValue[0].empty())
                        this->menu->createModeValue[0] = "0";
                    int size = std::stoi(this->menu->createModeValue[0]);
                    this->linkedList->createLinkedList(size);
                } else if (createMode == constants::MenuDataStructure::CreateMode::Button::DEFINED_LIST_BUTTON) {
                    if (this->menu->createModeValue[1] == "None")
                        break;
                    std::vector<std::string> values;
                    std::string value = this->menu->createModeValue[1];
                    std::stringstream ss(value);
                    std::string token;
                    while (std::getline(ss, token, ',')) {
                        values.push_back(token);
                    }
                    this->linkedList->createLinkedList(values);
                } else if (createMode == constants::MenuDataStructure::CreateMode::Button::FILE_BUTTON) {
                    if (this->menu->createModeValue[2] == "None")
                        break;
                    std::vector<std::string> values;
                    std::string value = this->menu->createModeValue[2];
                    std::stringstream ss(value);
                    std::string token;
                    while (std::getline(ss, token, ','))
                        values.push_back(token);
                    this->linkedList->createLinkedList(values);
                    this->menu->createModeValue[2] = "None";
                }
                this->controlMenu->reset();
                break;
            case constants::MenuDataStructure::Button::PUSH_BUTTON:
                if (this->menu->pushModeValue == "None")
                    break;

                this->linkedList->addNode(
                        0,
                        this->menu->pushModeValue,
                        this->pushModeEvents(0)
                        );

                std::cout << "Pushed " << this->menu->pushModeValue << std::endl;
                this->menu->pushModeValue = "None";
                this->controlMenu->reset();
                break;
            case constants::MenuDataStructure::Button::POP_BUTTON:
                if (this->menu->getActiveOptionMenu() != constants::MenuDataStructure::Button::POP_BUTTON)
                    break;

                this->linkedList->deleteNode(
                        0,
                        this->popModeEvents(0)
                        );

                std::cout << "Popped " << std::endl;
                this->menu->resetActiveOptionMenuOnly();
                this->controlMenu->reset();
                break;
            case constants::MenuDataStructure::Button::CLEAR_BUTTON:
                if (this->menu->getActiveOptionMenu() != constants::MenuDataStructure::Button::CLEAR_BUTTON)
                    break;

                this->linkedList->createLinkedList(0);

                std::cout << "Cleared " << std::endl;
                this->menu->resetActiveOptionMenuOnly();
                this->controlMenu->reset();
                break;
        }
    }

    this->controlMenu->update();

    this->linkedList->processControlMenu(this->controlMenu->getStatus());
    this->linkedList->setSpeed(this->controlMenu->getSpeed());

    this->linkedList->update();
}

void StackScene::render() {
    if (this->isMenuOpen)
        this->menu->render();

    if (this->isDemoCodeOpen)
        this->linkedList->renderHighlighter();

    this->controlMenu->render();
    this->linkedList->render();
}

void StackScene::pollEvent(sf::Event event, sf::Vector2f mousePosView) {
    if (this->isMenuOpen)
        this->menu->pollEvents(event, mousePosView);

    this->controlMenu->pollEvents(event, mousePosView);
}

void StackScene::init() {
    this->menu = new MenuDataStructure(this->window);
    this->linkedList = new LinkedList(this->window, LinkedList::TypeLinkedList::SINGLY);
}

void StackScene::reset() {
    this->menu->resetActiveOptionMenu();
}

std::vector<EventAnimation> StackScene::pushModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    if (chosenNode < 0 || chosenNode > this->linkedList->getSize())
        return {};

    // init highlighter later
    // ....

    std::vector<EventAnimation> events;
    EventAnimation event;

    events.emplace_back(event);

    return events;
}

std::vector<EventAnimation> StackScene::popModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    if (chosenNode < 0 || chosenNode >= this->linkedList->getSize())
        return {};

    // init highlighter later
    // ....

    std::vector<EventAnimation> events;
    EventAnimation event;

    event.statusChosenNode = NodeInfo::StatusNode::Visible;
    events.emplace_back(event);

    return events;
}
