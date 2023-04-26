//
// Created by dirii on 29/03/2023.
//

#ifndef VISUALGO_CS162_QUEUESCENE_HPP
#define VISUALGO_CS162_QUEUESCENE_HPP

#include "BaseScene.hpp"
#include "MenuDataStructure.hpp"
#include "core/LinkedList.hpp"

class QueueScene : public BaseScene{
private:
    MenuDataStructure* menu;
    LinkedList* linkedList;

    void init();

public:
    explicit QueueScene(sf::RenderWindow* window);

    void reset();

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;

    std::vector<EventAnimation> pushModeEvents(int chosenNode);
    std::vector<EventAnimation> popModeEvents(int chosenNode);
};

#endif //VISUALGO_CS162_QUEUESCENE_HPP
