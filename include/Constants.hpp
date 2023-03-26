//
// Created by dirii on 23/03/2023.
//

#ifndef VISUALGO_CS162_CONSTANTS_HPP
#define VISUALGO_CS162_CONSTANTS_HPP

#include <SFML/Graphics.hpp>

namespace constants{
    static enum Scene{
        MAIN_MENU_SCENE = 1,
        SINGLY_LINKED_LIST_SCENE,
        DOUBLY_LINKED_LIST_SCENE,
        CIRCULAR_LINKED_LIST_SCENE,
        STACK_SCENE,
        QUEUE_SCENE,
        STATIC_ARRAY_SCENE,
        DYNAMIC_ARRAY_SCENE,
    } scene = MAIN_MENU_SCENE;

    static int Width = 1760,
        Height = 992;
    constexpr char *titleWindow = "Visualgo CS162 - Phan Minh Quang";
    static int fps = 60;

    static sf::Color normalGreen = sf::Color(0, 255, 0),
                        hoverGreen = sf::Color(0, 200, 0),
                        clickGreen = sf::Color(0, 150, 0);

    static sf::Color normalGray = sf::Color(200, 200, 200),
                        hoverGray = sf::Color(150, 150, 150),
                        clickGray = sf::Color(100, 100, 100);

    // positions of buttons
    static sf::Vector2f submenuButtonPos = sf::Vector2f(0, 700),
            demoCodeButtonPos = sf::Vector2f(1736, 700);

    // size of buttons
    static sf::Vector2f sideButtonSize = sf::Vector2f(24, 180);

    // rounding button
    static int CORNER_POINT_COUNT_BUTTON = 15,
                CORNER_RADIUS_BUTTON = 5;
}

#endif //VISUALGO_CS162_CONSTANTS_HPP
