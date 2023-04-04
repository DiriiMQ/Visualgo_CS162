//
// Created by dirii on 27/03/2023.
//

#ifndef VISUALGO_CS162_DYNAMICARRAYSCENE_HPP
#define VISUALGO_CS162_DYNAMICARRAYSCENE_HPP

#include "BaseScene.hpp"

class DynamicArrayScene : public BaseScene{
public:
    explicit DynamicArrayScene(sf::RenderWindow* window);

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;
};

#endif //VISUALGO_CS162_DYNAMICARRAYSCENE_HPP
