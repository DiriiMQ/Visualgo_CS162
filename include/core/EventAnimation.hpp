//
// Created by dirii on 16/04/2023.
//

#ifndef VISUALGO_CS162_EVENTANIMATION_HPP
#define VISUALGO_CS162_EVENTANIMATION_HPP

#include "draw/NodeInfo.hpp"

class EventAnimation{
public:
    int textNode[4]{};
    std::vector<std::pair<int, NodeInfo::ArrowType>> colorArrows;
    std::vector<std::pair<int, NodeInfo::ArrowType>> hiddenArrows;
    std::vector<int> colorNodes;
    NodeInfo::StatusNode statusChosenNode;
    bool isPrintPreVal, isPrintNormal;
    std::vector<int> lines;

    EventAnimation();

    void reset();
};

#endif //VISUALGO_CS162_EVENTANIMATION_HPP
