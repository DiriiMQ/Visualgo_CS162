//
// Created by dirii on 12/04/2023.
//

#include "LinkedList.hpp"

LinkedList::LinkedList(sf::RenderWindow* window, TypeLinkedList typeLinkedList) {
    this->window = window;
    this->typeLinkedList = typeLinkedList;
    this->highlighter = nullptr;
    this->delayTime = constants::LinkedList::DELAY_TIME;
    this->backArrow = new BackArrow(this->window, {0, 0}, {0, 0});

    if (this->typeLinkedList == TypeLinkedList::CIRCULAR)
        this->backArrow->show();
    else
        this->backArrow->hide();

    this->createLinkedList(0);
}

void LinkedList::clear() {
    for (auto &node : this->nodes)
        delete node;
    this->nodes.clear();
    this->size = 0;
}

void LinkedList::render() {
    if (this->size > 1) {
//        this->backArrow->toggleActiveColorNode();
        this->backArrow->render();
    }
    for (auto &node : this->nodes){
        node->render();
    }
}

LinkedList::LinkedList(sf::RenderWindow* window, TypeLinkedList typeLinkedList, int size) {
    this->window = window;
    this->typeLinkedList = typeLinkedList;
    this->highlighter = nullptr;
    this->delayTime = constants::LinkedList::DELAY_TIME;
    this->backArrow = new BackArrow(this->window, {0, 0}, {0, 0});

    if (this->typeLinkedList == TypeLinkedList::CIRCULAR)
        this->backArrow->show();
    else
        this->backArrow->hide();

    this->createLinkedList(size);
}

LinkedList::LinkedList(sf::RenderWindow* window, TypeLinkedList typeLinkedList, std::vector<std::string> values) {
    this->window = window;
    this->typeLinkedList = typeLinkedList;
    this->highlighter = nullptr;
    this->delayTime = constants::LinkedList::DELAY_TIME;
    this->backArrow = new BackArrow(this->window, {0, 0}, {0, 0});

    if (this->typeLinkedList == TypeLinkedList::CIRCULAR)
        this->backArrow->show();
    else
        this->backArrow->hide();

    this->createLinkedList(std::move(values));
}

void LinkedList::update() {
    if ((int)this->events.size() && (this->isDelay or this->clock.getElapsedTime().asSeconds() > this->delayTime / this->speed))
        this->updateAnimation();
    this->isDelay = false;
}

void LinkedList::updateAnimation() {
    if (this->nodes.empty())
        return;

    // reset events of list
    for (auto &node : this->nodes){
        node->reset();
    }

    EventAnimation &event = this->events[this->currentEvent];
    for (auto &arrow: event.colorArrows)
        this->nodes[arrow.first]->toggleActiveColorArrow(arrow.second);
    for (auto &arrow : event.hiddenArrows)
        this->nodes[arrow.first]->hide(arrow.second);
    for (auto node : event.colorNodes)
        this->nodes[node]->toggleActiveColorNode();
    switch (event.statusChosenNode) {
        case NodeInfo::StatusNode::InChain:
            this->nodes[this->chosenNode]->setNodeInChain();
            break;
        case NodeInfo::StatusNode::OutChain:
            this->nodes[this->chosenNode]->setNodeOutside();
            break;
        case NodeInfo::StatusNode::Visible:
            this->nodes[this->chosenNode]->setNodeVisible();
            break;
    }
    if (event.isPrintPreVal)
        this->nodes[this->chosenNode]->setPrintPreVal();
    if (this->chosenNode < this->size - 1 && event.isPrintNormal)
        this->nodes[this->chosenNode + 1]->setPrintNormal();

    this->backArrow->setPosition(event.posBackArrow[0], event.posBackArrow[1]);

    if (this->highlighter)
        this->highlighter->toggle(event.lines);

    this->calculateEffectivePositions();

    for (auto &node : this->nodes){
        node->updateNode();
    }

    for (auto &i : event.titleNodes) {
        this->nodes[i.first]->setTitle(i.second);
    }

    if (this->chosenNode < this->size - 1)
        this->nodes[this->chosenNode]->updateArrows(NodeInfo::ArrowType::RIGHT, this->nodes[this->chosenNode + 1]->getPosition());
    if (this->chosenNode > 0)
        this->nodes[this->chosenNode]->updateArrows(NodeInfo::ArrowType::LEFT, this->nodes[this->chosenNode - 1]->getPosition());

    int lastInChain = 0;
    if (this->nodes[lastInChain]->getStatusNode() != NodeInfo::StatusNode::InChain){
        lastInChain++;
    }
    for (int i = lastInChain + 1; i < this->size; i++){
        if (this->nodes[i]->getStatusNode() == NodeInfo::StatusNode::InChain) {
            this->nodes[lastInChain]->updateArrows(NodeInfo::ArrowType::RIGHT, this->nodes[i]->getPosition());
            this->nodes[i]->updateArrows(NodeInfo::ArrowType::LEFT, this->nodes[lastInChain]->getPosition());
            lastInChain = i;
        }
    }
}

void LinkedList::calculateEffectivePositions() {
    if (this->size < 2) return;

    int lastInChain = 0;
    if (this->nodes[lastInChain]->getStatusNode() != NodeInfo::StatusNode::InChain){
        lastInChain++;
    }

    this->nodes[lastInChain]->setEffectivePosition(
            sf::Vector2f(
                    constants::NodeInfo::originNode.x,
                    constants::NodeInfo::originNode.y
            )
    );

    for (int i = lastInChain + 1; i < this->size; i++){
        if (this->nodes[i]->getStatusNode() == NodeInfo::StatusNode::InChain){
            this->nodes[i]->setEffectivePosition(
                    sf::Vector2f(
                            this->nodes[lastInChain]->getPosition().x + constants::NodeInfo::offsetX,
                            this->nodes[lastInChain]->getPosition().y
                    )
            );
            lastInChain = i;
        }
    }
}

void LinkedList::resetEvents() {
    delete this->highlighter;
    this->highlighter = nullptr;
    this->currentEvent = 0;
    this->events.clear();
    this->chosenNode = 0;

    if (this->deletedNode != -1){
        this->nodes.erase(this->nodes.begin() + this->deletedNode);
        --this->size;
        if (this->size && this->deletedNode == this->size)
            this->nodes.back()->destroyArrow(NodeInfo::ArrowType::RIGHT);
        if (this->size && this->deletedNode == 0)
            this->nodes[0]->destroyArrow(NodeInfo::ArrowType::LEFT);
    }
    this->deletedNode = -1;

    for (int i = 0;  i < this->size; i++){
        this->nodes[i]->reset();
        this->nodes[i]->reInitPos(i);
        this->nodes[i]->reInitPreVal();
    }
}

void LinkedList::createLinkedList(int _size) {
    this->resetEvents();
    this->size = _size;
    for (auto &node : this->nodes)
        delete node;
    this->nodes.resize(_size);
    for (int i = 0; i < size; i++){
        this->nodes[i] = new NodeInfo(
                this->window,
                std::to_string(Random::randomInt(0, 99)),
                sf::Vector2f(
                        constants::NodeInfo::originNode.x + static_cast<float>(i) * constants::NodeInfo::offsetX,
                        constants::NodeInfo::originNode.y
                ),
                this->typeLinkedList == TypeLinkedList::DOUBLY
        );
        if (i > 0){
            this->nodes[i - 1]->initArrow(
                    NodeInfo::ArrowType::RIGHT,
                    this->nodes[i - 1]->getPosition(),
                    this->nodes[i]->getPosition()
            );
            if (this->typeLinkedList == TypeLinkedList::DOUBLY)
                this->nodes[i]->initArrow(
                        NodeInfo::ArrowType::LEFT,
                        this->nodes[i]->getPosition(),
                        this->nodes[i - 1]->getPosition()
                );
        }
    }
    if (this->size > 1)
        this->backArrow->setPosition(this->nodes.back()->getPosition(), this->nodes[0]->getPosition());
}

void LinkedList::createLinkedList(std::vector<std::string> values) {
    this->resetEvents();
    this->size = static_cast<int>(values.size());
    for (auto &node : this->nodes)
        delete node;
    this->nodes.resize(this->size);
    for (int i = 0; i < this->size; i++){
        this->nodes[i] = new NodeInfo(
                this->window,
                values[i],
                sf::Vector2f(
                        constants::NodeInfo::originNode.x + static_cast<float>(i) * constants::NodeInfo::offsetX,
                        constants::NodeInfo::originNode.y
                ),
                this->typeLinkedList == TypeLinkedList::DOUBLY
        );
        if (i > 0){
            this->nodes[i - 1]->initArrow(
                    NodeInfo::ArrowType::RIGHT,
                    this->nodes[i - 1]->getPosition(),
                    this->nodes[i]->getPosition()
            );
            if (this->typeLinkedList == TypeLinkedList::DOUBLY)
                this->nodes[i]->initArrow(
                        NodeInfo::ArrowType::LEFT,
                        this->nodes[i]->getPosition(),
                        this->nodes[i - 1]->getPosition()
                );
        }
    }
    if (this->size > 1)
        this->backArrow->setPosition(this->nodes.back()->getPosition(), this->nodes[0]->getPosition());
}

void LinkedList::initHighlighter(int linesCount, const char *codePath) {
    delete this->highlighter;
    this->highlighter = new Highlighter(
            this->window,
            linesCount,
            codePath
    );
}

void LinkedList::toggleLines(std::vector<int> lines) {
    this->highlighter->toggle(std::move(lines));
}

void LinkedList::renderHighlighter() {
    if (this->highlighter)
        this->highlighter->render();
}

void LinkedList::processControlMenu(ControlMenu::StatusCode status) {
    if (this->clock.getElapsedTime().asSeconds() < this->delayTime / this->speed)
        return;
    switch (status){
        case ControlMenu::StatusCode::PREVIOUS:
            if (this->currentEvent > 0)
                --this->currentEvent;
            break;
        case ControlMenu::StatusCode::PAUSE:
//            std::cout << "PAUSE" << std::endl;
            break;
        case ControlMenu::StatusCode::PLAY:
            if (this->currentEvent + 1 < this->events.size()) {
                this->isDelay = true;
                this->clock.restart();
            }
        case ControlMenu::StatusCode::NEXT:
            if (this->currentEvent + 1 < this->events.size())
                ++this->currentEvent;
            break;
        default:
            break;
    }
}

void LinkedList::setSpeed(float _speed) {
    this->speed = _speed;
}

int LinkedList::getSize() const {
    return this->size;
}

void LinkedList::addNode(int position, std::string value, const std::vector<EventAnimation>& listEvents) {
    if (position < 0 || position > this->size) return;

    sf::Vector2f newPosition(
            constants::NodeInfo::originNode.x + static_cast<float>(this->nodes.size()) * constants::NodeInfo::offsetX,
            constants::NodeInfo::originNode.y
    );
    if (this->size) {
        this->nodes.back()->initArrow(
                NodeInfo::ArrowType::RIGHT,
                this->nodes.back()->getPosition(),
                newPosition
        );
    }
    this->nodes.push_back(new NodeInfo(
            this->window,
            "10",
            newPosition,
            this->typeLinkedList == TypeLinkedList::DOUBLY
    ));
    ++this->size;
    if (this->typeLinkedList == TypeLinkedList::DOUBLY && this->size > 1)
        this->nodes.back()->initArrow(
                NodeInfo::ArrowType::LEFT,
                this->nodes.back()->getPosition(),
                this->nodes[this->nodes.size() - 2]->getPosition()
        );
    for (int i = this->size - 1; i > position; --i) {
        this->nodes[i]->setValue(this->nodes[i - 1]->getValue());
        this->nodes[i]->reInitPreVal();
    }
    this->nodes[position]->setValue(std::move(value));

    this->chosenNode = position;
    this->currentEvent = 0;

    for (auto &e : listEvents)
        this->events.emplace_back(e);
}

void LinkedList::deleteNode(int position, const std::vector<EventAnimation>& listEvents) {
    if (position < 0 || position >= this->size) return;

    this->deletedNode = position;
    this->chosenNode = position;
    this->currentEvent = 0;

    for (auto &e : listEvents)
        this->events.emplace_back(e);
}

void LinkedList::updateNode(int position, std::string value, const std::vector<EventAnimation> &listEvents) {
    if (position < 0 || position >= this->size) return;

    this->nodes[position]->setValue(std::move(value));
    this->chosenNode = position;
    this->currentEvent = 0;

    for (auto &e : listEvents)
        this->events.emplace_back(e);
}

void LinkedList::searchNode(const std::vector<EventAnimation> &listEvents) {
    this->chosenNode = 0;
    this->currentEvent = 0;

    for (auto &e : listEvents)
        this->events.emplace_back(e);
}

int LinkedList::findValue(const std::string& value) {
    for (int i = 0; i < this->size; ++i)
        if (this->nodes[i]->getValue() == value)
            return i;
    return this->size;
}
