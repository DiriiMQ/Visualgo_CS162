//
// Created by dirii on 28/03/2023.
//

#ifndef VISUALGO_CS162_CLLSCENE_HPP
#define VISUALGO_CS162_CLLSCENE_HPP

#include "BaseScene.hpp"

class CLLScene : public BaseScene{
public:
    explicit CLLScene(sf::RenderWindow* window);

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;
};

#endif //VISUALGO_CS162_CLLSCENE_HPP
