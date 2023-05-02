//
// Created by dirii on 27/03/2023.
//

#ifndef VISUALGO_CS162_STATICARRAYSCENE_HPP
#define VISUALGO_CS162_STATICARRAYSCENE_HPP

#include "BaseScene.hpp"
#include "MenuArray.hpp"
#include "core/Array.hpp"

class StaticArrayScene : public BaseScene{
private:
    MenuArray* menu;
    Array* array;

    void init();

public:
    explicit StaticArrayScene(sf::RenderWindow* window);

    void reset();

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;

    std::vector<EventAnimation> addModeEvents(int chosenNode);
    std::vector<EventAnimation> deleteModeEvents(int chosenNode);
    std::vector<EventAnimation> updateModeEvents(int chosenNode);
    std::vector<EventAnimation> searchModeEvents(int chosenNode);
};

#endif //VISUALGO_CS162_STATICARRAYSCENE_HPP
