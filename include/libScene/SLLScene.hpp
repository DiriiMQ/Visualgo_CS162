//
// Created by dirii on 26/03/2023.
//

#ifndef VISUALGO_CS162_SLLSCENE_HPP
#define VISUALGO_CS162_SLLSCENE_HPP

#include "BaseScene.hpp"
#include "MenuLinkedList.hpp"
#include "core/LinkedList.hpp"

#include "Highlighter.hpp"

class SLLScene : public BaseScene {
private:
//    sf::Text* text;
//    sf::Font* font;
    MenuLinkedList* menu;
//    NodeInfo* node;
//    Arrow* arrow;
    LinkedList* linkedList;
    Highlighter* highlighter;

    void init();

public:
    explicit SLLScene(sf::RenderWindow* window);

    void reset();

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;
};

#endif //VISUALGO_CS162_SLLSCENE_HPP
