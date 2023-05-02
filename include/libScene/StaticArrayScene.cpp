//
// Created by dirii on 27/03/2023.
//

#include "StaticArrayScene.hpp"

StaticArrayScene::StaticArrayScene(sf::RenderWindow *window) : BaseScene(window) {
    this->init();
}

void StaticArrayScene::update() {
    if (this->isMenuOpen) {
        this->menu->update();

        constants::MenuArray::Button status = this->menu->getActiveOptionMenu();
        constants::MenuArray::CreateMode::Button createMode;
        switch (status){
            case constants::MenuArray::Button::CREATE_BUTTON:
                createMode = this->menu->getActiveCreateMode();
                if (createMode == constants::MenuArray::CreateMode::Button::RANDOM_BUTTON) {
                    if (this->menu->createModeValue[0] == "None")
                        break;
                    if (this->menu->createModeValue[0].empty())
                        this->menu->createModeValue[0] = "0";
                    int size = std::stoi(this->menu->createModeValue[0]);
                    this->array->createArray(size);
                } else if (createMode == constants::MenuArray::CreateMode::Button::DEFINED_LIST_BUTTON) {
                    if (this->menu->createModeValue[1] == "None")
                        break;
                    std::vector<std::string> values;
                    std::string value = this->menu->createModeValue[1];
                    std::stringstream ss(value);
                    std::string token;
                    while (std::getline(ss, token, ',')) {
                        values.push_back(token);
                    }
                    this->array->createArray(values);
                } else if (createMode == constants::MenuArray::CreateMode::Button::FILE_BUTTON) {
                    if (this->menu->createModeValue[2] == "None")
                        break;
                    std::vector<std::string> values;
                    std::string value = this->menu->createModeValue[2];
                    std::stringstream ss(value);
                    std::string token;
                    while (std::getline(ss, token, ','))
                        values.push_back(token);
                    this->array->createArray(values);
                    this->menu->createModeValue[2] = "None";
                }
                this->controlMenu->reset();
                break;
            case constants::MenuArray::Button::ADD_BUTTON:
                if (this->menu->addModeValue[0] == "None" || this->menu->addModeValue[1] == "None" || this->menu->addModeValue[0].empty())
                    break;

                this->array->addSquare(
                        std::stoi(this->menu->addModeValue[0]),
                        this->menu->addModeValue[1],
                        this->addModeEvents(std::stoi(this->menu->addModeValue[0]))
                );

                std::cout << "Add: " << this->menu->addModeValue[0] << " " << this->menu->addModeValue[1] << std::endl;
                this->menu->addModeValue[0] = this->menu->addModeValue[1] = "None";
                this->controlMenu->reset();
                break;
            case constants::MenuArray::Button::DELETE_BUTTON:
                if (this->menu->deleteModeValue == "None" || this->menu->deleteModeValue.empty())
                    break;

                this->array->deleteSquare(
                        std::stoi(this->menu->deleteModeValue),
                        this->deleteModeEvents(std::stoi(this->menu->deleteModeValue))
                );

                std::cout << "Delete: " << this->menu->deleteModeValue << std::endl;
                this->menu->deleteModeValue = "None";
                this->controlMenu->reset();
                break;
            case constants::MenuArray::Button::UPDATE_BUTTON:
                if (this->menu->updateModeValue[0] == "None" || this->menu->updateModeValue[1] == "None" || this->menu->updateModeValue[0].empty())
                    break;

                this->array->updateSquare(
                        std::stoi(this->menu->updateModeValue[0]),
                        this->menu->updateModeValue[1],
                        this->updateModeEvents(std::stoi(this->menu->updateModeValue[0]))
                );

                std::cout << "Update: " << this->menu->updateModeValue[0] << " " << this->menu->updateModeValue[1] << std::endl;
                this->menu->updateModeValue[0] = this->menu->updateModeValue[1] = "None";
                this->controlMenu->reset();
                break;
            case constants::MenuArray::Button::SEARCH_BUTTON:
                if (this->menu->searchModeValue == "None" || this->menu->searchModeValue.empty())
                    break;

                this->array->searchSquare(
                        this->searchModeEvents(this->array->findValue(this->menu->searchModeValue))
                );

                std::cout << "Search: " << this->menu->searchModeValue << std::endl;
                this->menu->searchModeValue = "None";
                this->controlMenu->reset();
                break;
        }
    }

    this->controlMenu->update();

    this->array->processControlMenu(this->controlMenu->getStatus());
    this->array->setSpeed(this->controlMenu->getSpeed());

    this->array->update();
}

void StaticArrayScene::render() {
    if (this->isMenuOpen)
        this->menu->render();

    if (this->isDemoCodeOpen)
        this->array->renderHighlighter();

    this->controlMenu->render();
    this->array->render();
}

void StaticArrayScene::pollEvent(sf::Event event, sf::Vector2f mousePosView) {
    if (this->isMenuOpen)
        this->menu->pollEvents(event, mousePosView);

    this->controlMenu->pollEvents(event, mousePosView);
}

void StaticArrayScene::init() {
    this->menu = new MenuArray(this->window, constants::MenuArray::Type::STATIC);
    this->array = new Array(this->window, Array::TypeArray::STATIC);
}

void StaticArrayScene::reset() {
    this->menu->resetActiveOptionMenu();
}

std::vector<EventAnimation> StaticArrayScene::addModeEvents(int chosenNode) {
    this->array->resetEvents();
    if (chosenNode < 0 || chosenNode > this->array->getSize())
        return {};

    // init highlighter
    // ...

    int size = this->array->getSize() + 1,
            squaresSize = this->array->getSquaresSize();
    if (size > squaresSize) --size;
    if (!squaresSize) return {};

    std::vector<EventAnimation> events;
    EventAnimation event;

    if (size < squaresSize) {
        event = EventAnimation();
        event.eventSquares.assign(squaresSize, EventSquare());
        for (auto &square: event.eventSquares) {
            square.status = Square::Status::active;
            square.isPrintPreVal = true;
        }
        for (int i = size - 1; i < squaresSize; ++i)
            event.eventSquares[i].status = Square::Status::inactive;
        if (size > 1)
            event.eventSquares[size - 2].title = "n";

        events.emplace_back(event);

        event = EventAnimation();
        event.eventSquares.assign(squaresSize, EventSquare());
        for (auto &square : event.eventSquares) {
            square.status = Square::Status::active;
            square.isPrintPreVal = true;
        }
        for (int i = size; i < squaresSize; ++i)
            event.eventSquares[i].status = Square::Status::inactive;
        event.eventSquares[size - 1].title = "n";

        events.emplace_back(event);
    }

    for (int i = size - 1; i >= chosenNode; --i) {
        event = EventAnimation();
        event.eventSquares.assign(squaresSize, EventSquare());
        for (auto &square: event.eventSquares) {
            square.status = Square::Status::active;
            square.isPrintPreVal = true;
        }
        for (int j = size; j < squaresSize; ++j)
            event.eventSquares[j].status = Square::Status::inactive;
        event.eventSquares[size - 1].title = "n";
        for (int j = size - 1; j > i; --j)
            event.eventSquares[j].isPrintPreVal = false;
        event.eventSquares[i].status = Square::Status::chosen;

        events.emplace_back(event);

        event.eventSquares[i].isPrintPreVal = false;
        if (i > chosenNode)
            event.eventSquares[i - 1].status = Square::Status::chosen;

        events.emplace_back(event);
    }

    return events;
}

std::vector<EventAnimation> StaticArrayScene::deleteModeEvents(int chosenNode) {
    this->array->resetEvents();
    if (chosenNode < 0 || chosenNode >= this->array->getSize())
        return {};

    // init highlighter
    // ...

    int size = this->array->getSize(),
            squaresSize = this->array->getSquaresSize();
    std::vector<EventAnimation> events;
//    events.reserve(100);
    EventAnimation event;

    for (int i = chosenNode; i < size - 1; ++i) {
        event = EventAnimation();
        event.eventSquares.assign(squaresSize, EventSquare());
        for (auto &square : event.eventSquares) {
            square.status = Square::Status::active;
            square.isPrintPreVal = true;
        }
        for (int j = size; j < squaresSize; ++j)
            event.eventSquares[j].status = Square::Status::inactive;
        for (int j = 0; j < i; ++j)
            event.eventSquares[j].isPrintPreVal = false;
        event.eventSquares[i].status = Square::Status::chosen;
        for (auto &square : event.eventSquaresTemp)
            square.status = Square::Status::hidden;
        event.eventSquares[size - 1].title = "n";

        events.emplace_back(event);

        event.eventSquares[i].isPrintPreVal = false;
        event.eventSquares[i + 1].status = Square::Status::chosen;

        events.emplace_back(event);
    }

    event = EventAnimation();
    event.eventSquares.assign(squaresSize, EventSquare());
    for (int i = 0; i < size - 1; ++i) {
        event.eventSquares[i].status = Square::Status::active;
        if (i == size - 2)
            event.eventSquares[i].title = "n";
    }
    for (int i = size - 1; i < squaresSize; ++i)
        event.eventSquares[i].status = Square::Status::inactive;

    events.emplace_back(event);

    return events;
}

std::vector<EventAnimation> StaticArrayScene::updateModeEvents(int chosenNode) {
    this->array->resetEvents();
    if (chosenNode < 0 || chosenNode >= this->array->getSize())
        return {};

    // init highlighter
    // ...

    std::vector<EventAnimation> events;
    EventAnimation event;

    event = EventAnimation();
    event.eventSquares.assign(this->array->getSquaresSize(), EventSquare());
    for (int i = 0; i < this->array->getSize(); ++i) {
        event.eventSquares[i].status = Square::Status::active;
        if (i == this->array->getSize() - 1)
            event.eventSquares[this->array->getSize() - 1].title = "n";
    }
    event.eventSquares[chosenNode].status = Square::Status::chosen;
    event.eventSquares[chosenNode].isPrintPreVal = true;

    events.emplace_back(event);

    event.eventSquares[chosenNode].isPrintPreVal = false;

    events.emplace_back(event);

    return events;
}

std::vector<EventAnimation> StaticArrayScene::searchModeEvents(int chosenNode) {
    this->array->resetEvents();

    // init highlighter
    // ...

    int size = this->array->getSize(),
            squaresSize = this->array->getSquaresSize();
    std::vector<EventAnimation> events;
    EventAnimation event;

    for (int i = 0; i <= chosenNode; ++i) {
        if (i == size) break;

        event = EventAnimation();
        event.eventSquares.assign(squaresSize, EventSquare());
        for (int j = 0; j < size; ++j) {
            event.eventSquares[j].status = Square::Status::active;
            if (j == size - 1)
                event.eventSquares[size - 1].title = "n";
        }
        event.eventSquares[i].status = Square::Status::chosen;

        events.emplace_back(event);
    }

    if (chosenNode == size) {
        event = EventAnimation();
        event.eventSquares.assign(squaresSize, EventSquare());
        for (int j = 0; j < size; ++j) {
            event.eventSquares[j].status = Square::Status::active;
            if (j == size - 1)
                event.eventSquares[size - 1].title = "n";
        }

        events.emplace_back(event);
    }

    return events;
}
