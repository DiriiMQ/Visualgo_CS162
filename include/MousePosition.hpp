//
// Created by dirii on 23/03/2023.
//

#ifndef VISUALGO_CS162_MOUSEPOSITION_HPP
#define VISUALGO_CS162_MOUSEPOSITION_HPP

#include <SFML/Graphics.hpp>

class MousePosition{
protected:
    sf::RenderWindow* relativeWindow;

    sf::Vector2i mousePos;
    sf::Vector2f mousePosView;
public:
    void updateMousePosition();
};

#endif //VISUALGO_CS162_MOUSEPOSITION_HPP
