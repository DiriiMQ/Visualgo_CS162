//
// Created by dirii on 29/03/2023.
//

#ifndef VISUALGO_CS162_QUEUESCENE_HPP
#define VISUALGO_CS162_QUEUESCENE_HPP

#include "BaseScene.hpp"

class QueueScene : public BaseScene{
public:
    explicit QueueScene(sf::RenderWindow* window);

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;
};

#endif //VISUALGO_CS162_QUEUESCENE_HPP
