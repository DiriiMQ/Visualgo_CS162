//
// Created by dirii on 16/04/2023.
//

#include "EventAnimation.hpp"

EventAnimation::EventAnimation() {
    for (int& i : this->textNode)
        i = -1;

    this->statusChosenNode = NodeInfo::StatusNode::InChain;
    this->isPrintPreVal = this->isPrintNormal = false;
}
