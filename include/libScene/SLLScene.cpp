//
// Created by dirii on 26/03/2023.
//

#include "SLLScene.hpp"

void SLLScene::pollEvent(sf::Event event, sf::Vector2f mousePosView) {
    if (this->isMenuOpen)
        this->menu->pollEvents(event, mousePosView);

    this->controlMenu->pollEvents(event, mousePosView);
}

void SLLScene::update() {
    if (this->isMenuOpen) {
        this->menu->update();

        constants::MenuLinkedList::Button status = this->menu->getActiveOptionMenu();
        constants::MenuLinkedList::CreateMode::Button createMode;
        switch (status){
            case constants::MenuLinkedList::Button::CREATE_BUTTON:
                createMode = this->menu->getActiveCreateMode();
                if (createMode == constants::MenuLinkedList::CreateMode::Button::RANDOM_BUTTON) {
                    if (this->menu->createModeValue[0] == "None")
                        break;
                    if (this->menu->createModeValue[0].empty())
                        this->menu->createModeValue[0] = "0";
                    int size = std::stoi(this->menu->createModeValue[0]);
                    this->linkedList->createLinkedList(size);
                } else if (createMode == constants::MenuLinkedList::CreateMode::Button::DEFINED_LIST_BUTTON) {
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
                }
                this->controlMenu->reset();
                break;
            case constants::MenuLinkedList::Button::ADD_BUTTON:
                if (this->menu->addModeValue[0] == "None" || this->menu->addModeValue[1] == "None")
                    break;
                if (this->menu->addModeValue[0].empty())
                    break;
                this->linkedList->addNode(std::stoi(this->menu->addModeValue[0]), this->menu->addModeValue[1]);
//                std::cout << "Add: " << this->menu->addModeValue[0] << " " << this->menu->addModeValue[1] << std::endl;
                this->menu->addModeValue[0] = this->menu->addModeValue[1] = "None";
                this->controlMenu->reset();
                break;
        }
    }

    this->controlMenu->update();

//    this->linkedList->toggleLines(std::vector<int>{0, 2, 3, 11});
    this->linkedList->processControlMenu(this->controlMenu->getStatus());
    this->linkedList->setSpeed(this->controlMenu->getSpeed());

    this->linkedList->update();
//    std::cout << "Speed: " << this->controlMenu->getSpeed() << std::endl;
}

void SLLScene::render() {
    if (this->isMenuOpen)
        this->menu->render();

    if (this->isDemoCodeOpen)
        this->linkedList->renderHighlighter();

    this->controlMenu->render();
    this->linkedList->render();
}

SLLScene::SLLScene(sf::RenderWindow *window) : BaseScene(window) {
    this->init();
}

void SLLScene::init() {
    this->menu = new MenuLinkedList(this->window);
    this->linkedList = new LinkedList(this->window, LinkedList::TypeLinkedList::SINGLY);
}

void SLLScene::reset() {
    this->menu->resetActiveOptionMenu();
}
