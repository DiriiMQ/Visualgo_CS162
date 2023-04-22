//
// Created by dirii on 12/04/2023.
//

#ifndef VISUALGO_CS162_LINKEDLIST_HPP
#define VISUALGO_CS162_LINKEDLIST_HPP

#include <random>
#include "draw/NodeInfo.hpp"
#include "libScene/Highlighter.hpp"
#include "libScene/ControlMenu.hpp"
#include "EventAnimation.hpp"

namespace Random{
    static std::mt19937 rng(std::random_device{}());
    static int randomInt(int min, int max){
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }
}

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

private:
    sf::RenderWindow* window;
    sf::Clock clock;
    int chosenNode = 0;
    TypeLinkedList typeLinkedList;

    std::vector<NodeInfo*> nodes;
    int size;

    Highlighter* highlighter;

    std::vector<EventAnimation> events;
    int currentEvent;

    float speed, delayTime;
    bool isDelay = false;
};

#endif //VISUALGO_CS162_LINKEDLIST_HPP
