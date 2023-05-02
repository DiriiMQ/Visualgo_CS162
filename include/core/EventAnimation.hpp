//
// Created by dirii on 16/04/2023.
//

#ifndef VISUALGO_CS162_EVENTANIMATION_HPP
#define VISUALGO_CS162_EVENTANIMATION_HPP

#include "draw/NodeInfo.hpp"
#include "draw/SquareInfo.hpp"

struct EventSquare{
    Square::Status status = Square::Status::inactive;
    bool isPrintPreVal = false;
    std::string title{};
};

class EventAnimation{
public:
    // for linked list
    std::vector<std::pair<int, std::string>> titleNodes;
    std::vector<std::pair<int, NodeInfo::ArrowType>> colorArrows;
    std::vector<std::pair<int, NodeInfo::ArrowType>> hiddenArrows;
    std::vector<int> colorNodes;
    NodeInfo::StatusNode statusChosenNode;
    bool isPrintPreVal, isPrintNormal, isShowBackArrow;
    std::pair<int, int> indexBackArrow;

    // for array
    std::vector<EventSquare> eventSquares{}, eventSquaresTemp{};

    std::vector<int> lines;

    EventAnimation();

    void reset();
};

#endif //VISUALGO_CS162_EVENTANIMATION_HPP
