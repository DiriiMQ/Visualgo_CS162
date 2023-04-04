//
// Created by dirii on 30/03/2023.
//

#ifndef VISUALGO_CS162_MAINMENU_HPP
#define VISUALGO_CS162_MAINMENU_HPP

#include "BaseScene.hpp"

class MainMenu : public BaseScene{
public:
    explicit MainMenu(sf::RenderWindow* window);

    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    void update() override;
    void render() override;
};

#endif //VISUALGO_CS162_MAINMENU_HPP
