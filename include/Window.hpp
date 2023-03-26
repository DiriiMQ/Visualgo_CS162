//
// Created by dirii on 23/03/2023.
//

#ifndef VISUALGO_CS162_WINDOW_HPP
#define VISUALGO_CS162_WINDOW_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MousePosition.hpp"
#include "Constants.hpp"
#include "Stuff.hpp"

class Window : public MousePosition{
private:
    sf::RenderWindow* window{};
    sf::VideoMode videoMode;
    sf::Event event{};

    // buttons
    Button* submenuButton,
            *demoCodeButton;

    void initWindow();
    void init();
public:
    Window();
    ~Window() = default;

    const bool running() const;

    void pollEvent();

    void update();

    void render();
};

#endif //VISUALGO_CS162_WINDOW_HPP
