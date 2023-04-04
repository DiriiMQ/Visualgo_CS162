//
// Created by dirii on 23/03/2023.
//

#ifndef VISUALGO_CS162_WINDOW_HPP
#define VISUALGO_CS162_WINDOW_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MousePosition.hpp"
#include "Constants.hpp"
#include "stuff/button.hpp"
#include "libScene/AllScenes.hpp"

class Window : public MousePosition{
private:
    sf::RenderWindow* window{};
    sf::VideoMode videoMode;
    sf::Event event{};

    // scenes
    class BaseScene* scenes[constants::sceneVariables::SCENE_COUNT];
    constants::sceneVariables::Scene currentScene;

    // buttons
    Button* submenuButton,
            *demoCodeButton;

    void initWindow();
    void initScenes();
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
