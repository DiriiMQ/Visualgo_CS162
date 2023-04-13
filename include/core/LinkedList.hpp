//
// Created by dirii on 12/04/2023.
//

#ifndef VISUALGO_CS162_LINKEDLIST_HPP
#define VISUALGO_CS162_LINKEDLIST_HPP

#include <vector>
#include <random>
#include "draw/NodeInfo.hpp"

namespace Random{
    static std::mt19937 rng(std::random_device{}());
    static int randomInt(int min, int max){
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }
}

class LinkedList {
private:
    sf::RenderWindow* window;
    std::vector<NodeInfo*> nodes;
    int size;
public:
    explicit LinkedList(sf::RenderWindow* window);
    LinkedList(sf::RenderWindow* window, int size);
    LinkedList(sf::RenderWindow* window, std::vector<std::string> values);
    void addNode(NodeInfo* node);
    void removeNode(int index);
    void clear();
    void render();
    [[nodiscard]] int getSize() const;
    NodeInfo* getNode(int index);
};

#endif //VISUALGO_CS162_LINKEDLIST_HPP
