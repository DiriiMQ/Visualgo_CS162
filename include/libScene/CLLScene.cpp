//
// Created by dirii on 28/03/2023.
//

#include "CLLScene.hpp"

CLLScene::CLLScene(sf::RenderWindow *window) : BaseScene(window) {
    this->init();
}

void CLLScene::pollEvent(sf::Event event, sf::Vector2f mousePosView) {
    if (this->isMenuOpen)
        this->menu->pollEvents(event, mousePosView);

    this->controlMenu->pollEvents(event, mousePosView);
}

void CLLScene::update() {
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
                } else if (createMode == constants::MenuLinkedList::CreateMode::Button::FILE_BUTTON) {
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
            case constants::MenuLinkedList::Button::ADD_BUTTON:
                if (this->menu->addModeValue[0] == "None" || this->menu->addModeValue[1] == "None" || this->menu->addModeValue[0].empty())
                    break;

                this->linkedList->addNode(
                        std::stoi(this->menu->addModeValue[0]),
                        this->menu->addModeValue[1],
                        this->addModeEvents(std::stoi(this->menu->addModeValue[0]))
                );

                std::cout << "Add: " << this->menu->addModeValue[0] << " " << this->menu->addModeValue[1] << std::endl;
                this->menu->addModeValue[0] = this->menu->addModeValue[1] = "None";
                this->controlMenu->reset();
                break;
            case constants::MenuLinkedList::Button::DELETE_BUTTON:
                if (this->menu->deleteModeValue == "None" || this->menu->deleteModeValue.empty())
                    break;

                this->linkedList->deleteNode(
                        std::stoi(this->menu->deleteModeValue),
                        this->deleteModeEvents(std::stoi(this->menu->deleteModeValue))
                );

                std::cout << "Delete: " << this->menu->deleteModeValue << std::endl;
                this->menu->deleteModeValue = "None";
                this->controlMenu->reset();
                break;
            case constants::MenuLinkedList::Button::UPDATE_BUTTON:
                if (this->menu->updateModeValue[0] == "None" || this->menu->updateModeValue[1] == "None" || this->menu->updateModeValue[0].empty())
                    break;

                this->linkedList->updateNode(
                        std::stoi(this->menu->updateModeValue[0]),
                        this->menu->updateModeValue[1],
                        this->updateModeEvents(std::stoi(this->menu->updateModeValue[0]))
                );

                std::cout << "Update: " << this->menu->updateModeValue[0] << " " << this->menu->updateModeValue[1] << std::endl;
                this->menu->updateModeValue[0] = this->menu->updateModeValue[1] = "None";
                this->controlMenu->reset();
                break;
            case constants::MenuLinkedList::Button::SEARCH_BUTTON:
                if (this->menu->searchModeValue == "None" || this->menu->searchModeValue.empty())
                    break;

                this->linkedList->searchNode(
                        this->searchModeEvents(this->linkedList->findValue(this->menu->searchModeValue))
                );

                std::cout << "Search: " << this->menu->searchModeValue << std::endl;
                this->menu->searchModeValue = "None";
                this->controlMenu->reset();
                break;
        }
    }

    this->controlMenu->update();

    this->linkedList->processControlMenu(this->controlMenu->getStatus());
    this->linkedList->setSpeed(this->controlMenu->getSpeed());

    this->linkedList->update();
}

void CLLScene::render() {
    if (this->isMenuOpen)
        this->menu->render();

    if (this->isDemoCodeOpen)
        this->linkedList->renderHighlighter();

    this->controlMenu->render();
    this->linkedList->render();
}

void CLLScene::init() {
    this->menu = new MenuLinkedList(this->window);
    this->linkedList = new LinkedList(this->window, LinkedList::TypeLinkedList::CIRCULAR);
}

void CLLScene::reset() {
    this->menu->resetActiveOptionMenu();
}

std::vector<EventAnimation> CLLScene::addModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    if (chosenNode < 0 || chosenNode > this->linkedList->getSize())
        return {};

    this->linkedList->initHighlighter(
            constants::Highlighter::SLL::CODES_PATH[0].second,
            constants::Highlighter::SLL::CODES_PATH[0].first
    );

    std::vector<EventAnimation> events;
    EventAnimation event;

    if (chosenNode) {
        event.titleNodes = {
                {0,          "head"},
                {chosenNode, "temp"}
        };
        event.indexBackArrow.second = 0;
    }
    else {
        event.titleNodes.emplace_back(chosenNode, "temp");
        if (this->linkedList->getSize()) {
            event.titleNodes.emplace_back(1, "head");
            event.indexBackArrow.second = 1;
        }
    }
    event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
    if (chosenNode && chosenNode == this->linkedList->getSize())
        event.hiddenArrows.emplace_back(chosenNode - 1, NodeInfo::ArrowType::RIGHT);
    event.colorNodes.push_back(chosenNode);
    event.statusChosenNode = NodeInfo::StatusNode::OutChain;
    event.indexBackArrow.first = this->linkedList->getSize();
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
            event.indexBackArrow = {this->linkedList->getSize(), 1};
            event.lines = {1, 2};

            events.emplace_back(event);
        }

        event.reset();
        event.titleNodes.emplace_back(chosenNode, "head|temp");
        event.lines = {3};
        event.statusChosenNode = NodeInfo::StatusNode::InChain;
        event.indexBackArrow = {this->linkedList->getSize(), 0};
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
        event.indexBackArrow = {this->linkedList->getSize(), 0};
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
            event.indexBackArrow = {this->linkedList->getSize(), 0};
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
            event.indexBackArrow = {this->linkedList->getSize(), 0};
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
            event.indexBackArrow = {this->linkedList->getSize(), 0};
            event.lines = {8};

            events.emplace_back(event);
        }

        event.reset();
        event.titleNodes = {
                {0, "head"},
                {chosenNode, "temp"}
        };
        event.statusChosenNode = NodeInfo::StatusNode::InChain;
        event.indexBackArrow = {this->linkedList->getSize(), 0};
        event.lines = {9};

        events.emplace_back(event);
    }

    return events;
}

std::vector<EventAnimation> CLLScene::deleteModeEvents(int chosenNode) {
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
        event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
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
            event.indexBackArrow = {this->linkedList->getSize() - 1, 1};
            event.lines = {2};

            events.emplace_back(event);
        }

        event.reset();
        event.titleNodes.emplace_back(1, "head");
        event.statusChosenNode = NodeInfo::StatusNode::Visible;
        event.indexBackArrow = {this->linkedList->getSize() - 1, 1};
        event.lines = {3};

        events.emplace_back(event);
    } else {
        event.reset();
        event.titleNodes.emplace_back(0, "head|current");
        event.colorNodes.push_back(0);
        event.statusChosenNode = NodeInfo::StatusNode::InChain;
        event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
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
            event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
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
            event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
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
        event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
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
            event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
            event.isPrintNormal = true;
            event.lines = {9};

            events.emplace_back(event);

            event.reset();
            event.titleNodes.emplace_back(0, "head");
            event.statusChosenNode = NodeInfo::StatusNode::Visible;
            event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
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
            event.indexBackArrow = {chosenNode - 1, 0};
            event.lines = {9};

            events.emplace_back(event);

            event.reset();
            event.titleNodes.emplace_back(0, "head");
            event.hiddenArrows.emplace_back(chosenNode - 1, NodeInfo::ArrowType::RIGHT);
            event.statusChosenNode = NodeInfo::StatusNode::Visible;
            event.indexBackArrow = {chosenNode - 1, 0};
            event.lines = {10};

            events.emplace_back(event);
        }
    }

    return events;
}

std::vector<EventAnimation> CLLScene::updateModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    if (chosenNode < 0 || chosenNode >= this->linkedList->getSize())
        return {};

    this->linkedList->initHighlighter(
            constants::Highlighter::SLL::CODES_PATH[2].second,
            constants::Highlighter::SLL::CODES_PATH[2].first
    );

    std::vector<EventAnimation> events;
    EventAnimation event;

    event.titleNodes.emplace_back(0, "head|current");
    event.colorNodes.push_back(0);
    event.isPrintPreVal = true;
    event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
    event.lines = {0};

    events.emplace_back(event);

    if (chosenNode) {
        for (int i = 0; i <= chosenNode; ++i) {
            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {i, "current"}
            };
            event.colorNodes.push_back(i);
            event.isPrintPreVal = true;
            event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
            event.lines = {1};

            events.emplace_back(event);

            if (i == chosenNode) break;

            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {i, "current"}
            };
            event.colorNodes.push_back(i);
            event.colorArrows.emplace_back(i, NodeInfo::ArrowType::RIGHT);
            event.isPrintPreVal = true;
            event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
            event.lines = {2};

            events.emplace_back(event);
        }
    }

    event.reset();
    if (chosenNode == 0)
        event.titleNodes.emplace_back(0, "head|current");
    else
        event.titleNodes = {
                {0, "head"},
                {chosenNode, "current"}
        };
    event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
    event.lines = {3};

    events.emplace_back(event);

    return events;
}

std::vector<EventAnimation> CLLScene::searchModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    this->linkedList->initHighlighter(
            constants::Highlighter::SLL::CODES_PATH[3].second,
            constants::Highlighter::SLL::CODES_PATH[3].first
    );

    std::vector<EventAnimation> events;
    EventAnimation event;

    event.titleNodes.emplace_back(0, "head|current");
    event.colorNodes.push_back(0);
    event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
    event.lines = {0};

    events.emplace_back(event);

    for (int i = 0; i <= chosenNode; ++i) {
        if (i == chosenNode && chosenNode == this->linkedList->getSize())
            break;

        event.reset();
        event.titleNodes = {
                {0, "head"},
                {i, "current"}
        };
        event.colorNodes.push_back(i);
        event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
        event.lines = {1};

        events.emplace_back(event);

        if (i == chosenNode) break;

        event.reset();
        event.titleNodes = {
                {0, "head"},
                {i, "current"}
        };
        event.colorNodes.push_back(i);
        event.colorArrows.emplace_back(i, NodeInfo::ArrowType::RIGHT);
        event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
        event.lines = {4};

        events.emplace_back(event);
    }

    if (chosenNode == this->linkedList->getSize()) {
        event.reset();
        event.titleNodes.emplace_back(0, "head");
        event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
        event.lines = {5};

        events.emplace_back(event);
    } else {
        event.reset();
        event.titleNodes = {
                {0, "head"},
                {chosenNode, "current"}
        };
        event.colorNodes.push_back(chosenNode);
        event.indexBackArrow = {this->linkedList->getSize() - 1, 0};
        event.lines = {2, 3};

        events.emplace_back(event);
    }

    return events;
}
