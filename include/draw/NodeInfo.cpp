//
// Created by dirii on 08/04/2023.
//

#include "NodeInfo.hpp"

NodeInfo::NodeInfo(sf::RenderWindow *window, std::string value, sf::Vector2f position, bool _isDLL) : BaseDraw(window) {
    this->values[0] = value;
    this->values[1] = value;

    this->positions[(int)TypeNode::Normal] = position;
    this->positions[(int)TypeNode::Effective] = position;
    this->positions[(int)TypeNode::Outside] = sf::Vector2f(
            position.x,
            position.y + constants::NodeInfo::offsetY
            );

    this->isDLL = _isDLL;

    this->statusNode = StatusNode::InChain;

    this->node = new SingleNode(window, std::move(value), this->positions[(int)TypeNode::Normal]);

    for (auto &arrow : this->arrows)
        arrow[(int)ArrowType::LEFT] = arrow[(int)ArrowType::RIGHT] = nullptr;

    this->isPrintPreVal = this->isPrintNormal = false;

    this->title.setFont(this->node->font);
    this->title.setCharacterSize(constants::TitleNode::fontSize);
    this->title.setFillColor(constants::titleGreen);
    this->title.setString("");
}

void NodeInfo::render() {
    if (this->statusNode == StatusNode::Visible)
        return;

    if (this->isDLL && this->statusNode == StatusNode::InChain){
        if (this->arrows[1][(int)ArrowType::LEFT])
            this->arrows[1][(int)ArrowType::LEFT]->render();
        if (this->arrows[1][(int)ArrowType::RIGHT])
            this->arrows[1][(int)ArrowType::RIGHT]->render();
    } else {
        if (this->arrows[0][(int)ArrowType::LEFT])
            this->arrows[0][(int)ArrowType::LEFT]->render();
        if (this->arrows[0][(int)ArrowType::RIGHT])
            this->arrows[0][(int)ArrowType::RIGHT]->render();
    }
    this->node->render();
    this->window->draw(this->title);
}

void NodeInfo::initArrow(NodeInfo::ArrowType type, sf::Vector2f start, sf::Vector2f end) {
    this->arrows[1][(int)type] = new Arrow(this->window, start, end);
    this->arrows[1][(int)type]->setMid();
    this->arrows[0][(int)type] = new Arrow(this->window, start, end);
}

void NodeInfo::toggleActiveColorNode() {
    this->node->toggleActiveColor();
}

void NodeInfo::toggleActiveColorArrow(NodeInfo::ArrowType type) {
    if (this->arrows[0][(int)type])
        this->arrows[0][(int)type]->toggleActiveColor();
    if (this->arrows[1][(int)type])
        this->arrows[1][(int)type]->toggleActiveColor();
}

void NodeInfo::resetColorNode() {
    this->node->resetColor();
}

void NodeInfo::resetColorArrow(NodeInfo::ArrowType type) {
    if (this->arrows[0][(int)type])
        this->arrows[0][(int)type]->resetColor();
    if (this->arrows[1][(int)type])
        this->arrows[1][(int)type]->resetColor();
}

void NodeInfo::reset() {
    this->resetColorNode();
    this->resetColorArrow(ArrowType::LEFT);
    this->resetColorArrow(ArrowType::RIGHT);
    this->resetTitle();
    this->isPrintNormal = this->isPrintPreVal = false;
    this->statusNode = StatusNode::InChain;
    this->show(ArrowType::LEFT);
    this->show(ArrowType::RIGHT);
}

// require update() before calling this function
sf::Vector2f NodeInfo::getPosition() {
    this->updateNode(); // ?
    return this->node->getPosition();
}

void NodeInfo::reInitPos(int index) {
    this->positions[(int)TypeNode::Normal] = sf::Vector2f(
            constants::NodeInfo::originNode.x + static_cast<float>(index) * constants::NodeInfo::offsetX,
            constants::NodeInfo::originNode.y
    );
    this->positions[(int)TypeNode::Outside] = sf::Vector2f(
            this->positions[(int)TypeNode::Effective].x,
            this->positions[(int)TypeNode::Effective].y + constants::NodeInfo::offsetY
            );
}

void NodeInfo::setPrintPreVal() {
    this->isPrintPreVal = true;
}

void NodeInfo::setPrintNormal() {
    this->isPrintNormal = true;
}

void NodeInfo::setNodeOutside() {
    this->statusNode = StatusNode::OutChain;
}

void NodeInfo::setNodeInChain() {
    this->statusNode = StatusNode::InChain;
}

void NodeInfo::setNodeVisible() {
    this->statusNode = StatusNode::Visible;
}

// require calculate effective positions of a chain before calling this function
void NodeInfo::updateNode() {
    if (this->statusNode == StatusNode::Visible)
        return;

    if (this->statusNode == StatusNode::InChain) {
        if (this->isPrintNormal) {
            this->node->setPosition(this->positions[(int)TypeNode::Normal]);
        } else {
            this->node->setPosition(this->positions[(int)TypeNode::Effective]);
        }
    } else {
        this->node->setPosition(this->positions[(int)TypeNode::Outside]);
    }

    if (this->isPrintPreVal) {
        this->node->setText(this->values[1]);
    } else {
        this->node->setText(this->values[0]);
    }
}

void NodeInfo::updateArrows(ArrowType type, sf::Vector2f end){
    if (this->arrows[0][(int)type])
        this->arrows[0][(int)type]->setPositions(this->node->getPosition(), end, false);

    if (this->arrows[1][(int)type])
        this->arrows[1][(int)type]->setPositions(this->node->getPosition(), end, true);
}

void NodeInfo::reInitPreVal() {
    this->values[1] = this->values[0];
}

NodeInfo::StatusNode NodeInfo::getStatusNode() {
    return this->statusNode;
}

void NodeInfo::setEffectivePosition(sf::Vector2f start) {
    this->positions[(int)TypeNode::Effective] = start;
}

void NodeInfo::setArrows(NodeInfo::ArrowType type, sf::Vector2f start, sf::Vector2f end) {
    if (this->arrows[0][(int)type])
        this->arrows[0][(int)type]->setPositions(start, end, false);
    if (this->arrows[1][(int)type])
        this->arrows[1][(int)type]->setPositions(start, end, true);
}

void NodeInfo::hide(NodeInfo::ArrowType type) {
    if (this->arrows[0][(int)type])
        this->arrows[0][(int)type]->hide();
    if (this->arrows[1][(int)type])
        this->arrows[1][(int)type]->hide();
}

void NodeInfo::show(NodeInfo::ArrowType type) {
    if (this->arrows[0][(int)type])
        this->arrows[0][(int)type]->show();
    if (this->arrows[1][(int)type])
        this->arrows[1][(int)type]->show();
}

NodeInfo::~NodeInfo() {
    delete this->node;
    for (auto & arrow : this->arrows) {
        for (auto & j : arrow) {
            delete j;
        }
    }
}

void NodeInfo::setValue(std::string value) {
    this->values[0] = std::move(value);
}

std::string NodeInfo::getValue() {
    return this->values[0];
}

void NodeInfo::setTitle(const std::string& _title) {
    std::string preTitle = this->title.getString();
    if (!preTitle.empty())
        preTitle += "|";
    preTitle += _title;
    this->title.setString(preTitle);
    sf::Vector2f pos = this->node->getPosition();
    this->title.setOrigin(
            this->title.getGlobalBounds().width / 2,
            this->title.getGlobalBounds().height / 2
            );
    this->title.setPosition(
            pos.x,
            pos.y + constants::TitleNode::offsetY
            );
}

void NodeInfo::resetTitle() {
    this->title.setString("");
}

void NodeInfo::destroyArrow(NodeInfo::ArrowType type) {
    if (this->arrows[0][(int)type])
        delete this->arrows[0][(int)type];
    if (this->arrows[1][(int)type])
        delete this->arrows[1][(int)type];
    this->arrows[0][(int)type] = nullptr;
    this->arrows[1][(int)type] = nullptr;
}
