//
// Created by dirii on 27/03/2023.
//

#ifndef VISUALGO_CS162_DLLSCENE_HPP
#define VISUALGO_CS162_DLLSCENE_HPP

#include "BaseScene.hpp"
#include "MenuLinkedList.hpp"
#include "core/LinkedList.hpp"

class DLLScene : public BaseScene {
private:
    MenuLinkedList* menu;
    LinkedList* linkedList;

    void init();

public:
    explicit DLLScene(sf::RenderWindow* window);

    void reset();

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;

    std::vector<EventAnimation> addModeEvents(int chosenNode);
    std::vector<EventAnimation> deleteModeEvents(int chosenNode);
    std::vector<EventAnimation> updateModeEvents(int chosenNode);
    std::vector<EventAnimation> searchModeEvents(int chosenNode);
};

#endif //VISUALGO_CS162_DLLSCENE_HPP
