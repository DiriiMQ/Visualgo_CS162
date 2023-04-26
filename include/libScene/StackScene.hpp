//
// Created by dirii on 28/03/2023.
//

#ifndef VISUALGO_CS162_STACKSCENE_HPP
#define VISUALGO_CS162_STACKSCENE_HPP

#include "BaseScene.hpp"
#include "MenuDataStructure.hpp"
#include "core/LinkedList.hpp"

class StackScene : public BaseScene{
private:
    MenuDataStructure* menu;
    LinkedList* linkedList;

    void init();

public:
    explicit StackScene(sf::RenderWindow* window);

    void reset();

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;

    std::vector<EventAnimation> pushModeEvents(int chosenNode);
    std::vector<EventAnimation> popModeEvents(int chosenNode);
};

#endif //VISUALGO_CS162_STACKSCENE_HPP
