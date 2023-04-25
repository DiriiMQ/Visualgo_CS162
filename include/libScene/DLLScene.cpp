//
// Created by dirii on 27/03/2023.
//

#include "DLLScene.hpp"

DLLScene::DLLScene(sf::RenderWindow *window) : BaseScene(window) {
    this->init();
}

void DLLScene::pollEvent(sf::Event event, sf::Vector2f mousePosView) {
    if (this->isMenuOpen)
        this->menu->pollEvents(event, mousePosView);

    this->controlMenu->pollEvents(event, mousePosView);
}

void DLLScene::update() {
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

void DLLScene::render() {
    if (this->isMenuOpen)
        this->menu->render();

    if (this->isDemoCodeOpen)
        this->linkedList->renderHighlighter();

    this->controlMenu->render();
    this->linkedList->render();
}

void DLLScene::init() {
    this->menu = new MenuLinkedList(this->window);
    this->linkedList = new LinkedList(this->window, LinkedList::TypeLinkedList::DOUBLY);
}

void DLLScene::reset() {
    this->menu->resetActiveOptionMenu();
}

std::vector<EventAnimation> DLLScene::addModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    if (chosenNode < 0 || chosenNode > this->linkedList->getSize())
        return {};

    std::vector<EventAnimation> events;
    EventAnimation event;
    int size = this->linkedList->getSize();

    if (chosenNode == 0) {
        this->linkedList->initHighlighter(
                constants::Highlighter::DLL::CODES_PATH[0].second,
                constants::Highlighter::DLL::CODES_PATH[0].first
        );

        event.titleNodes.emplace_back(chosenNode, "temp");
        if (size == 1)
            event.titleNodes.emplace_back(1, "head|tail");
        else if (size > 1){
            event.titleNodes.emplace_back(1, "head");
            event.titleNodes.emplace_back(size, "tail");
        }
        if (size)
            event.hiddenArrows.emplace_back(1, NodeInfo::ArrowType::LEFT);
        event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
        event.colorNodes.emplace_back(chosenNode);
        event.statusChosenNode = NodeInfo::StatusNode::OutChain;
        event.lines = {0, 1};

        events.emplace_back(event);

        event.reset();

        event.titleNodes.emplace_back(chosenNode, "temp");
        if (size == 1)
            event.titleNodes.emplace_back(1, "head|tail");
        else if (size > 1){
            event.titleNodes.emplace_back(1, "head");
            event.titleNodes.emplace_back(size, "tail");
        }
        if (size)
            event.hiddenArrows.emplace_back(1, NodeInfo::ArrowType::LEFT);
        event.colorArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
        event.colorNodes.emplace_back(chosenNode);
        event.statusChosenNode = NodeInfo::StatusNode::OutChain;
        event.isPrintNormal = true;
        event.lines = {2};

        events.emplace_back(event);

        if (size) {
            event.reset();
            event.titleNodes.emplace_back(chosenNode, "temp");
            if (size == 1)
                event.titleNodes.emplace_back(1, "head|tail");
            else if (size > 1){
                event.titleNodes.emplace_back(1, "head");
                event.titleNodes.emplace_back(size, "tail");
            }
            event.colorArrows = {
//                    {chosenNode, NodeInfo::ArrowType::RIGHT},
                    {chosenNode + 1, NodeInfo::ArrowType::LEFT}
            };
            event.colorNodes.emplace_back(chosenNode + 1);
            event.statusChosenNode = NodeInfo::StatusNode::InChain;
            event.lines = {3, 4};

            events.emplace_back(event);
        }

        event.reset();
        if (size) {
            event.titleNodes = {
                    {chosenNode, "head"},
                    {size,       "tail"}
            };
            event.lines = {7};
        }
        else {
            event.titleNodes.emplace_back(chosenNode, "head|tail");
            event.lines = {5, 6, 7};
        }
        event.colorNodes = {chosenNode};

        events.emplace_back(event);
    }
    else if (chosenNode == size) {
        this->linkedList->initHighlighter(
                constants::Highlighter::DLL::CODES_PATH[1].second,
                constants::Highlighter::DLL::CODES_PATH[1].first
        );

        event.titleNodes.emplace_back(chosenNode, "temp");
        if (size == 1)
            event.titleNodes.emplace_back(0, "head|tail");
        else if (size > 1){
            event.titleNodes.emplace_back(0, "head");
            event.titleNodes.emplace_back(size - 1, "tail");
        }
        event.hiddenArrows.emplace_back(size - 1, NodeInfo::ArrowType::RIGHT);
        event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::LEFT);
        event.colorNodes.emplace_back(chosenNode);
        event.statusChosenNode = NodeInfo::StatusNode::OutChain;
        event.lines = {0, 1};

        events.emplace_back(event);

        event.reset();

        event.titleNodes.emplace_back(chosenNode, "temp");
        if (size == 1)
            event.titleNodes.emplace_back(0, "head|tail");
        else if (size > 1){
            event.titleNodes.emplace_back(0, "head");
            event.titleNodes.emplace_back(size - 1, "tail");
        }
        event.hiddenArrows.emplace_back(size - 1, NodeInfo::ArrowType::RIGHT);
        event.colorArrows.emplace_back(chosenNode, NodeInfo::ArrowType::LEFT);
        event.colorNodes.emplace_back(chosenNode);
        event.statusChosenNode = NodeInfo::StatusNode::OutChain;
        event.lines = {2};

        events.emplace_back(event);

        event.reset();
        event.titleNodes.emplace_back(chosenNode, "temp");
        if (size == 1)
            event.titleNodes.emplace_back(0, "head|tail");
        else if (size > 1){
            event.titleNodes.emplace_back(0, "head");
            event.titleNodes.emplace_back(size - 1, "tail");
        }
        event.colorArrows = {
//                {chosenNode, NodeInfo::ArrowType::LEFT},
                {chosenNode - 1, NodeInfo::ArrowType::RIGHT}
        };
        event.colorNodes.emplace_back(chosenNode - 1);
        event.statusChosenNode = NodeInfo::StatusNode::InChain;
        event.lines = {3};

        events.emplace_back(event);

        event.reset();
        event.titleNodes = {
                {chosenNode, "tail"},
                {0, "head"}
        };
        event.colorNodes = {chosenNode};
        event.lines = {4};

        events.emplace_back(event);
    }
    else {
        this->linkedList->initHighlighter(
                constants::Highlighter::DLL::CODES_PATH[2].second,
                constants::Highlighter::DLL::CODES_PATH[2].first
        );

        event.titleNodes = {
                {chosenNode, "temp"},
                {0,          "head"},
                {size,       "tail"}
        };
        event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
        event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::LEFT);
        event.colorNodes.emplace_back(chosenNode);
        event.statusChosenNode = NodeInfo::StatusNode::OutChain;
        event.lines = {0, 1};

        events.emplace_back(event);

        event.reset();
        event.titleNodes = {
                {chosenNode, "temp"},
                {0,          "head|current"},
                {size,       "tail"}
        };
        event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
        event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::LEFT);
        event.colorNodes.emplace_back(0);
        event.statusChosenNode = NodeInfo::StatusNode::OutChain;
        event.lines = {2};

        events.emplace_back(event);

        for (int i = 0; i < chosenNode; ++i) {
            event.reset();
            event.titleNodes = {
                    {chosenNode, "temp"},
                    {0,          "head"},
                    {size,       "tail"},
                    {i, "current"}
            };
            event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
            event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::LEFT);
            event.colorNodes.emplace_back(i);
            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.lines = {3};

            events.emplace_back(event);

            if (i == chosenNode - 1)
                break;

            event.reset();
            event.titleNodes = {
                    {chosenNode, "temp"},
                    {0,          "head"},
                    {size,       "tail"},
                    {i, "current"}
            };
            event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::RIGHT);
            event.hiddenArrows.emplace_back(chosenNode, NodeInfo::ArrowType::LEFT);
            event.colorArrows.emplace_back(i, NodeInfo::ArrowType::RIGHT);
//            event.colorArrows.emplace_back(i + 1 + (i + 1 == chosenNode), NodeInfo::ArrowType::LEFT);
            event.colorNodes.emplace_back(i);
            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.lines = {4};

            events.emplace_back(event);
        }

        event.reset();
        event.titleNodes = {
                {chosenNode, "temp"},
                {0,          "head"},
                {size,       "tail"},
                {chosenNode - 1, "current"}
        };
        event.colorArrows = {
                {chosenNode, NodeInfo::ArrowType::RIGHT},
                {chosenNode, NodeInfo::ArrowType::LEFT}
        };
        event.colorNodes.emplace_back(chosenNode);
        event.statusChosenNode = NodeInfo::StatusNode::OutChain;
        event.isPrintNormal = true;
        event.lines = {5, 6};

        events.emplace_back(event);

        event.reset();
        event.titleNodes = {
                {chosenNode, "temp"},
                {0,          "head"},
                {size,       "tail"}
        };
        event.colorNodes.emplace_back(chosenNode);
        event.statusChosenNode = NodeInfo::StatusNode::InChain;
        event.lines = {7, 8};

        events.emplace_back(event);
    }

    return events;
}

std::vector<EventAnimation> DLLScene::deleteModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    if (chosenNode < 0 || chosenNode >= this->linkedList->getSize())
        return {};

    std::vector<EventAnimation> events;
    EventAnimation event;
    int size = this->linkedList->getSize();

    if (chosenNode == 0) {
        this->linkedList->initHighlighter(
                constants::Highlighter::DLL::CODES_PATH[3].second,
                constants::Highlighter::DLL::CODES_PATH[3].first
        );

        if (size == 1) {
            event.titleNodes.emplace_back(chosenNode, "head|tail|temp");
            event.colorNodes.emplace_back(chosenNode);
            event.statusChosenNode = NodeInfo::StatusNode::InChain;
            event.lines = {0, 1, 2};

            events.emplace_back(event);

            event.reset();
            event.statusChosenNode = NodeInfo::StatusNode::Visible;
            event.lines = {5, 6, 7};

            events.emplace_back(event);
        }
        else {
            event.titleNodes = {
                    {chosenNode, "head|temp"},
                    {size - 1, "tail"}
            };
            event.colorNodes.emplace_back(chosenNode);
            event.lines = {0, 1};

            events.emplace_back(event);

            event.reset();
            if (size == 2)
                event.titleNodes.emplace_back(size - 1, "head|tail");
            else
                event.titleNodes = {
                    {size - 1, "tail"},
                    {chosenNode + 1, "head" }
            };
            event.titleNodes.emplace_back(chosenNode, "temp");
            event.colorNodes.emplace_back(chosenNode + 1);
//            event.isPrintNormal = true;
//            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.lines = {2};

            events.emplace_back(event);

            event.reset();
            if (size == 2)
                event.titleNodes.emplace_back(size - 1, "head|tail");
            else
                event.titleNodes = {
                        {size - 1, "tail"},
                        {chosenNode + 1, "head" }
                };
            event.titleNodes.emplace_back(chosenNode, "temp");
            event.colorNodes.emplace_back(chosenNode);
            event.hiddenArrows = {
//                    {chosenNode, NodeInfo::ArrowType::RIGHT},
                    {chosenNode + 1, NodeInfo::ArrowType::LEFT}
            };
            event.statusChosenNode = NodeInfo::StatusNode::OutChain;
            event.isPrintNormal = true;
            event.lines = {3, 4};

            events.emplace_back(event);

            event.reset();
            if (size == 2)
                event.titleNodes.emplace_back(size - 1, "head|tail");
            else
                event.titleNodes = {
                        {size - 1, "tail"},
                        {chosenNode + 1, "head" }
                };
            event.hiddenArrows = {
                    {chosenNode + 1, NodeInfo::ArrowType::LEFT}
            };
            event.statusChosenNode = NodeInfo::StatusNode::Visible;
            event.lines = {7};

            events.emplace_back(event);
        }
    }
    else if (chosenNode == size - 1) {
        this->linkedList->initHighlighter(
                constants::Highlighter::DLL::CODES_PATH[4].second,
                constants::Highlighter::DLL::CODES_PATH[4].first
                );

        event.titleNodes = {
                {0, "head"},
                {chosenNode, "tail|temp"}
        };
        event.colorNodes.emplace_back(chosenNode);
        event.lines = {0, 1};

        events.emplace_back(event);

        event.reset();
        if (size == 2)
            event.titleNodes.emplace_back(0, "head|tail");
        else
            event.titleNodes = {
                    {chosenNode - 1, "tail"},
                    {0, "head" }
            };
        event.titleNodes.emplace_back(chosenNode, "temp");
        event.colorNodes.emplace_back(chosenNode - 1);
        event.lines = {2};

        events.emplace_back(event);

        event.reset();
        if (size == 2)
            event.titleNodes.emplace_back(0, "head|tail");
        else
            event.titleNodes = {
                    {chosenNode - 1, "tail"},
                    {0, "head" }
            };
        event.titleNodes.emplace_back(chosenNode, "temp");
        event.colorNodes.emplace_back(chosenNode);
        event.hiddenArrows = {
                {chosenNode - 1, NodeInfo::ArrowType::RIGHT}
        };
        event.statusChosenNode = NodeInfo::StatusNode::OutChain;
        event.isPrintNormal = true;
        event.lines = {3};

        events.emplace_back(event);

        event.reset();
        if (size == 2)
            event.titleNodes.emplace_back(0, "head|tail");
        else
            event.titleNodes = {
                    {chosenNode - 1, "tail"},
                    {0, "head" }
            };
        event.hiddenArrows = {
                {chosenNode - 1, NodeInfo::ArrowType::RIGHT}
        };
        event.statusChosenNode = NodeInfo::StatusNode::Visible;
        event.lines = {4};

        events.emplace_back(event);
    }
    else {
        this->linkedList->initHighlighter(
                constants::Highlighter::DLL::CODES_PATH[5].second,
                constants::Highlighter::DLL::CODES_PATH[5].first
        );

        event.titleNodes = {
                {0, "head|temp"},
                {size - 1, "tail"}
        };
        event.colorNodes.emplace_back(0);
        event.lines = {0, 1};

        events.emplace_back(event);

        for (int i = 0; i <= chosenNode; ++i) {
            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {i, "temp"},
                    {size - 1, "tail"}
            };
            event.colorNodes.emplace_back(i);
            event.lines = {2};

            events.emplace_back(event);

            if (i == chosenNode)
                break;

            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {i, "temp"},
                    {size - 1, "tail"}
            };
            event.colorNodes.emplace_back(i);
            event.colorArrows.emplace_back(i, NodeInfo::ArrowType::RIGHT);
            event.lines = {3};

            events.emplace_back(event);
        }

        event.reset();
        event.titleNodes = {
                {0, "head"},
                {chosenNode, "temp"},
                {size - 1, "tail"}
        };
        event.colorNodes.emplace_back(chosenNode);
        event.colorArrows = {
                {chosenNode - 1, NodeInfo::ArrowType::RIGHT},
                {chosenNode + 1, NodeInfo::ArrowType::LEFT}
        };
        event.statusChosenNode = NodeInfo::StatusNode::OutChain;
        event.isPrintNormal = true;
        event.lines = {4, 5};

        events.emplace_back(event);

        event.reset();
        event.titleNodes = {
                {0, "head"},
                {size - 1, "tail"}
        };
        event.statusChosenNode = NodeInfo::StatusNode::Visible;
        event.lines = {6};

        events.emplace_back(event);
    }

    return events;
}

std::vector<EventAnimation> DLLScene::updateModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    if (chosenNode < 0 || chosenNode >= this->linkedList->getSize())
        return {};

    this->linkedList->initHighlighter(
            constants::Highlighter::DLL::CODES_PATH[6].second,
            constants::Highlighter::DLL::CODES_PATH[6].first
    );

    std::vector<EventAnimation> events;
    EventAnimation event;
    int size = this->linkedList->getSize();

    if (size > 1)
        event.titleNodes = {
                {0, "head|current"},
                {size - 1, "tail"}
        };
    else
        event.titleNodes = {
                {0, "head|tail|current"}
        };
    event.colorNodes.push_back(0);
    event.isPrintPreVal = true;
    event.lines = {0};

    events.emplace_back(event);

    if (chosenNode) {
        for (int i = 0; i <= chosenNode; ++i) {
            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {size - 1, "tail"},
                    {i, "current"},
            };
            event.colorNodes.push_back(i);
            event.isPrintPreVal = true;
            event.lines = {1};

            events.emplace_back(event);

            if (i == chosenNode) break;

            event.reset();
            event.titleNodes = {
                    {0, "head"},
                    {i, "current"},
                    {size - 1, "tail"}
            };
            event.colorNodes.push_back(i);
            event.colorArrows.emplace_back(i, NodeInfo::ArrowType::RIGHT);
            event.isPrintPreVal = true;
            event.lines = {2};

            events.emplace_back(event);
        }
    }

    event.reset();
    if (size == 1)
        event.titleNodes = {
                {0, "head|tail|current"}
        };
    else if (chosenNode == size - 1)
        event.titleNodes = {
                {0, "head"},
                {chosenNode, "current|tail"}
        };
    else if (chosenNode == 0)
        event.titleNodes = {
                {0, "head|current"},
                {size - 1, "tail"}
        };
    else
        event.titleNodes = {
                {0,          "head"},
                {chosenNode, "current"},
                {size - 1,   "tail"}
        };
    event.lines = {3};

    events.emplace_back(event);

    return events;
}

std::vector<EventAnimation> DLLScene::searchModeEvents(int chosenNode) {
    this->linkedList->resetEvents();
    this->linkedList->initHighlighter(
            constants::Highlighter::DLL::CODES_PATH[7].second,
            constants::Highlighter::DLL::CODES_PATH[7].first
    );

    std::vector<EventAnimation> events;
    EventAnimation event;
    int size = this->linkedList->getSize();

    if (size > 1)
        event.titleNodes = {
                {0, "head|current"},
                {size - 1, "tail"}
        };
    else
        event.titleNodes = {
                {0, "head|tail|current"}
        };
    event.colorNodes.push_back(0);
    event.lines = {0};

    events.emplace_back(event);

    for (int i = 0; i <= chosenNode; ++i) {
        if (i == chosenNode && chosenNode == this->linkedList->getSize())
            break;

        event.reset();
        event.titleNodes = {
                {0, "head"},
                {size - 1, "tail"},
                {i, "current"}
        };
        event.colorNodes.push_back(i);
        event.lines = {1};

        events.emplace_back(event);

        if (i == chosenNode) break;

        event.reset();
        event.titleNodes = {
                {0, "head"},
                {size - 1, "tail"},
                {i, "current"}
        };
        event.colorNodes.push_back(i);
        event.colorArrows.emplace_back(i, NodeInfo::ArrowType::RIGHT);
        event.lines = {4};

        events.emplace_back(event);
    }

    if (chosenNode == this->linkedList->getSize()) {
        event.reset();
        event.titleNodes.emplace_back(0, "head");
        event.titleNodes.emplace_back(size - 1, "tail");
        event.lines = {5};

        events.emplace_back(event);
    } else {
        event.reset();
        event.titleNodes = {
                {0, "head"},
                {size - 1, "tail"},
                {chosenNode, "current"}
        };
        event.colorNodes.push_back(chosenNode);
        event.lines = {2, 3};

        events.emplace_back(event);
    }

    return events;
}
