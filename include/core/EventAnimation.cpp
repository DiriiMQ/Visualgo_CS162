//
// Created by dirii on 16/04/2023.
//

#include "EventAnimation.hpp"

EventAnimation::EventAnimation() {
    this->statusChosenNode = NodeInfo::StatusNode::InChain;
    this->isPrintPreVal = this->isPrintNormal = false;
}

void EventAnimation::reset() {
    this->titleNodes.clear();
    this->colorArrows.clear();
    this->hiddenArrows.clear();
    this->colorNodes.clear();
    this->lines.clear();

    this->statusChosenNode = NodeInfo::StatusNode::InChain;
    this->isPrintPreVal = this->isPrintNormal = false;
}
