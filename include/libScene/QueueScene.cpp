//
// Created by dirii on 29/03/2023.
//

#include "QueueScene.hpp"

QueueScene::QueueScene(sf::RenderWindow *window) : BaseScene(window) {
    this->init();
}

void QueueScene::update() {
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
                        this->linkedList->getSize(),
                        this->menu->pushModeValue,
                        this->pushModeEvents(this->linkedList->getSize())
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

void QueueScene::render() {
    if (this->isMenuOpen)
        this->menu->render();

    if (this->isDemoCodeOpen)
        this->linkedList->renderHighlighter();

    this->controlMenu->render();
    this->linkedList->render();
}

void QueueScene::pollEvent(sf::Event event, sf::Vector2f mousePosView) {
    if (this->isMenuOpen)
        this->menu->pollEvents(event, mousePosView);

    this->controlMenu->pollEvents(event, mousePosView);
}

void QueueScene::init() {
    this->menu = new MenuDataStructure(this->window);
    this->linkedList = new LinkedList(this->window, LinkedList::TypeLinkedList::SINGLY);
}

void QueueScene::reset() {
    this->menu->resetActiveOptionMenu();
}

std::vector<EventAnimation> QueueScene::pushModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    if (chosenNode < 0 || chosenNode > this->linkedList->getSize())
        return {};

    this->linkedList->initHighlighter(
            constants::Highlighter::SLL::CODES_PATH[0].second,
            constants::Highlighter::SLL::CODES_PATH[0].first
    );

    std::vector<EventAnimation> events;
    EventAnimation event;

    if (chosenNode)
        event.titleNodes = {
                {0, "head"},
                {chosenNode, "temp"}
        };
    else {
        event.titleNodes.emplace_back(chosenNode, "temp");
        if (this->linkedList->getSize())
            event.titleNodes.emplace_back(1, "head");
    }
    event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
    if (chosenNode && chosenNode == this->linkedList->getSize())
        event.hiddenArrows.emplace_back(chosenNode - 1, NodeInfo::ArrowType::RIGHT);
    event.colorNodes.push_back(chosenNode);
    event.statusChosenNode = NodeInfo::StatusNode::OutChain;
    event.lines = {0};

    events.emplace_back(event);

    if (chosenNode == 0) {
        if (this->linkedList->getSize()) {
            event.reset();
            event.titleNodes = {
                    {1, "head"},
                    {chosenNode, "temp"}
            };
            event.colorNodes = std::vector<int>{0};
            event.colorArrows.emplace_back(0, NodeInfo::ArrowType::RIGHT);
            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.isPrintNormal = true;
            event.lines = {1, 2};

            events.emplace_back(event);
        }

        event.reset();
        event.titleNodes.emplace_back(chosenNode, "head|temp");
        event.lines = {3};
        event.statusChosenNode = NodeInfo::StatusNode::InChain;
        events.emplace_back(event);
    } else {
        event.reset();
        event.titleNodes = {
                {0, "head|current"},
                {chosenNode, "temp"}
        };
        event.colorNodes.push_back(0);
        event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
        if (chosenNode == this->linkedList->getSize())
            event.hiddenArrows.emplace_back(chosenNode - 1, NodeInfo::ArrowType::RIGHT);
        event.statusChosenNode = NodeInfo::StatusNode::OutChain;
        event.lines = {5};

        events.emplace_back(event);

        for (int i = 0; i < chosenNode; ++i) {
            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {chosenNode, "temp"},
                    {i, "current"}
            };
            event.colorNodes.push_back(i);
            event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
            if (chosenNode == this->linkedList->getSize())
                event.hiddenArrows.emplace_back(chosenNode - 1, NodeInfo::ArrowType::RIGHT);
            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.lines = {6};

            events.emplace_back(event);

            if (i == chosenNode - 1) break;

            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {chosenNode, "temp"},
                    {i, "current"}
            };
            event.colorNodes.push_back(i);
            event.colorArrows.emplace_back(i, NodeInfo::ArrowType::RIGHT);
            event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
            if (chosenNode == this->linkedList->getSize())
                event.hiddenArrows.emplace_back(chosenNode - 1, NodeInfo::ArrowType::RIGHT);
            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.lines = {7};

            events.emplace_back(event);
        }

        if (chosenNode != this->linkedList->getSize()) {
            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {chosenNode, "temp"},
                    {chosenNode - 1, "current"}
            };
            event.colorNodes.push_back(chosenNode);
            event.colorArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.isPrintNormal = true;
            event.lines = {8};

            events.emplace_back(event);
        }

        event.reset();
        event.titleNodes = {
                {0, "head"},
                {chosenNode, "temp"}
        };
        event.statusChosenNode = NodeInfo::StatusNode::InChain;
        event.lines = {9};

        events.emplace_back(event);
    }

    return events;
}

std::vector<EventAnimation> QueueScene::popModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    if (chosenNode < 0 || chosenNode >= this->linkedList->getSize())
        return {};

    this->linkedList->initHighlighter(
            constants::Highlighter::SLL::CODES_PATH[1].second,
            constants::Highlighter::SLL::CODES_PATH[1].first
    );

    std::vector<EventAnimation> events;
    EventAnimation event;

    if (!chosenNode) {
        event.titleNodes.emplace_back(chosenNode, "head|temp");
        event.colorNodes.push_back(chosenNode);
        event.statusChosenNode = NodeInfo::StatusNode::InChain;
        event.lines = {0, 1};

        events.emplace_back(event);

        if (this->linkedList->getSize() > 1) {
            event.reset();
            event.titleNodes = {
                    {chosenNode, "temp"},
                    {1, "head"}
            };
            event.colorNodes.push_back(1);
            event.colorArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
            event.isPrintNormal = true;
            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.lines = {2};

            events.emplace_back(event);
        }

        event.reset();
        event.titleNodes.emplace_back(1, "head");
        event.statusChosenNode = NodeInfo::StatusNode::Visible;
        event.lines = {3};

        events.emplace_back(event);
    } else {
        event.reset();
        event.titleNodes.emplace_back(0, "head|current");
        event.colorNodes.push_back(0);
        event.statusChosenNode = NodeInfo::StatusNode::InChain;
        event.lines = {5};

        events.emplace_back(event);

        for (int i = 0; i < chosenNode; ++i) {
            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {i, "current"}
            };
            event.colorNodes.push_back(i);
            event.statusChosenNode = NodeInfo::StatusNode::InChain;
            event.lines = {6};

            events.emplace_back(event);

            if (i == chosenNode - 1) break;

            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {i, "current"}
            };
            event.colorNodes.push_back(i);
            event.colorArrows.emplace_back(i, NodeInfo::ArrowType::RIGHT);
            event.statusChosenNode = NodeInfo::StatusNode::InChain;
            event.lines = {7};

            events.emplace_back(event);
        }

        event.reset();
        event.titleNodes = {
                {0, "head"},
                {chosenNode, "temp"},
                {chosenNode - 1, "current"}
        };
        event.colorNodes.push_back(chosenNode);
        event.colorArrows.emplace_back(chosenNode - 1, NodeInfo::ArrowType::RIGHT);
        event.statusChosenNode = NodeInfo::StatusNode::InChain;
        event.lines = {8};

        events.emplace_back(event);

        if (chosenNode != this->linkedList->getSize() - 1) {
            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {chosenNode, "temp"},
                    {chosenNode - 1, "current"}
            };
            event.colorNodes.push_back(chosenNode);
            event.colorArrows.emplace_back(chosenNode - 1, NodeInfo::ArrowType::RIGHT);
            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.isPrintNormal = true;
            event.lines = {9};

            events.emplace_back(event);

            event.reset();
            event.titleNodes.emplace_back(0, "head");
            event.statusChosenNode = NodeInfo::StatusNode::Visible;
            event.lines = {10};

            events.emplace_back(event);
        } else {
            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {chosenNode, "temp"},
                    {chosenNode - 1, "current"}
            };
            event.colorNodes.push_back(chosenNode);
            event.hiddenArrows.emplace_back(chosenNode - 1, NodeInfo::ArrowType::RIGHT);
            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.lines = {9};

            events.emplace_back(event);

            event.reset();
            event.titleNodes.emplace_back(0, "head");
            event.hiddenArrows.emplace_back(chosenNode - 1, NodeInfo::ArrowType::RIGHT);
            event.statusChosenNode = NodeInfo::StatusNode::Visible;
            event.lines = {10};

            events.emplace_back(event);
        }
    }

    return events;
}
