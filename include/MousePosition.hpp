//
// Created by dirii on 23/03/2023.
//

#ifndef VISUALGO_CS162_MOUSEPOSITION_HPP
#define VISUALGO_CS162_MOUSEPOSITION_HPP

#include <SFML/Graphics.hpp>

/**
 * @brief A class to get the mouse position
 * 
 */
class MousePosition{
protected:
    sf::RenderWindow* relativeWindow; // the window to get the mouse position relative to

    sf::Vector2i mousePos; // the mouse position
    sf::Vector2f mousePosView; // the mouse position relative to the view
public:
    /**
     * @brief Update the mouse position
     * 
     */
    void updateMousePosition();
};

#endif //VISUALGO_CS162_MOUSEPOSITION_HPP
