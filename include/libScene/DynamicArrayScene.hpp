//
// Created by dirii on 27/03/2023.
//

#ifndef VISUALGO_CS162_DYNAMICARRAYSCENE_HPP
#define VISUALGO_CS162_DYNAMICARRAYSCENE_HPP

#include "BaseScene.hpp"
#include "MenuArray.hpp"
#include "core/Array.hpp"

class DynamicArrayScene : public BaseScene{
private:
    MenuArray* menu;
    Array* array;

    void init();

public:
    explicit DynamicArrayScene(sf::RenderWindow* window);

    void reset();

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;

    std::vector<EventAnimation> addModeEvents(int chosenNode);
    std::vector<EventAnimation> deleteModeEvents(int chosenNode);
    std::vector<EventAnimation> updateModeEvents(int chosenNode);
    std::vector<EventAnimation> searchModeEvents(int chosenNode);
    std::vector<EventAnimation> allocateModeEvents(int newSize);
};

#endif //VISUALGO_CS162_DYNAMICARRAYSCENE_HPP
