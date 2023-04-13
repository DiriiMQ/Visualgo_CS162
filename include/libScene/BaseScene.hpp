//
// Created by dirii on 23/03/2023.
//

#ifndef VISUALGO_CS162_BASESCENE_HPP
#define VISUALGO_CS162_BASESCENE_HPP

#include <SFML/Graphics.hpp>
#include "stuff/button.hpp"
#include "ControlMenu.hpp"

class BaseScene{
protected:
    sf::RenderWindow* window{};
    ControlMenu* controlMenu;

    void setWindow(sf::RenderWindow* window);
public:
    Button* modeButton{};
    bool isMenuOpen{}, isDemoCodeOpen{};

    explicit BaseScene(sf::RenderWindow* window);

    void createModeButton(sf::Vector2f position, std::string textString);

    virtual void pollEvent(sf::Event event, sf::Vector2f mousePosView) = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif //VISUALGO_CS162_BASESCENE_HPP
