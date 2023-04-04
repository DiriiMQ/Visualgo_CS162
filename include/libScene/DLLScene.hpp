//
// Created by dirii on 27/03/2023.
//

#ifndef VISUALGO_CS162_DLLSCENE_HPP
#define VISUALGO_CS162_DLLSCENE_HPP

#include "BaseScene.hpp"

class DLLScene : public BaseScene {
public:
    explicit DLLScene(sf::RenderWindow* window);

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;
};

#endif //VISUALGO_CS162_DLLSCENE_HPP
