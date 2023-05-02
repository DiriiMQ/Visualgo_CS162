//
// Created by dirii on 16/04/2023.
//

#include "EventAnimation.hpp"

EventAnimation::EventAnimation() {
    this->statusChosenNode = NodeInfo::StatusNode::InChain;
    this->isPrintPreVal = this->isPrintNormal = this->isShowBackArrow = false;
    this->indexBackArrow = {-1, -1};

    this->titleNodes = {};
    this->colorArrows = {};
    this->hiddenArrows = {};
    this->colorNodes = {};
    this->lines = {};

    this->eventSquares = {};
    this->eventSquaresTemp = {};
}

void EventAnimation::reset() {
    this->titleNodes.clear();
    this->colorArrows.clear();
    this->hiddenArrows.clear();
    this->colorNodes.clear();
    this->lines.clear();

    this->statusChosenNode = NodeInfo::StatusNode::InChain;
    this->isPrintPreVal = this->isPrintNormal = this->isShowBackArrow = false;
    this->indexBackArrow = {-1, -1};

    this->eventSquares.clear();
    this->eventSquaresTemp.clear();
}

EventAnimation::~EventAnimation() {
    this->titleNodes = {};
    this->colorArrows = {};
    this->hiddenArrows = {};
    this->colorNodes = {};
    this->lines = {};

    this->eventSquares = {};
    this->eventSquaresTemp = {};
}

EventAnimation &EventAnimation::operator=(const EventAnimation &other) = default;
