//
// Created by dirii on 12/04/2023.
//

#ifndef VISUALGO_CS162_LINKEDLIST_HPP
#define VISUALGO_CS162_LINKEDLIST_HPP

#include "Random.h"
#include "draw/NodeInfo.hpp"
#include "draw/BackArrow.hpp"
#include "libScene/Highlighter.hpp"
#include "libScene/ControlMenu.hpp"
#include "EventAnimation.hpp"
#include "core/Vector.h"

class LinkedList {
public:
    enum class TypeLinkedList{
        SINGLY,
        DOUBLY,
        CIRCULAR
    };

    explicit LinkedList(sf::RenderWindow* window, TypeLinkedList typeLinkedList);
    LinkedList(sf::RenderWindow* window, TypeLinkedList typeLinkedList, int size);
    LinkedList(sf::RenderWindow* window, TypeLinkedList typeLinkedList, std::vector<std::string> values);

    void setSpeed(float speed);
    int findValue(const std::string& value);
    sf::Vector2f getPosNode(int position);

    [[nodiscard]] int getSize() const;

    void update();
    void updateAnimation();
    void render();
    void renderHighlighter();
    void resetEvents();

    void calculateEffectivePositions();
    void clear();

    void processControlMenu(ControlMenu::StatusCode status);

    // operations of highlighter
    void initHighlighter(int linesCount, const char *codePath);
    void toggleLines(std::vector<int> lines);

    // operations of linked list
    void createLinkedList(int size);
    void createLinkedList(std::vector<std::string> values);
    void addNode(int position, std::string value, const std::vector<EventAnimation>& listEvents);
    void deleteNode(int position, const std::vector<EventAnimation>& listEvents);
    void updateNode(int position, std::string value, const std::vector<EventAnimation>& listEvents);
    void searchNode(const std::vector<EventAnimation>& listEvents);

private:
    sf::RenderWindow* window;
    sf::Clock clock;
    int chosenNode = 0, deletedNode = -1;
    TypeLinkedList typeLinkedList;

    Vector<NodeInfo*> nodes;
    int size;

    BackArrow* backArrow;

    Highlighter* highlighter;

    std::vector<EventAnimation> events;
    int currentEvent;

    float speed, delayTime;
    bool isDelay = false;
};

#endif //VISUALGO_CS162_LINKEDLIST_HPP
