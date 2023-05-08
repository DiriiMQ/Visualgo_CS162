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

/**
 * @brief The main window of the program
 * 
 */
class Window : public MousePosition{
private:
    sf::RenderWindow* window{}; // the window
    sf::VideoMode videoMode; // the video mode
    sf::Event event{}; // the event

    // scenes
    class BaseScene* scenes[constants::sceneVariables::SCENE_COUNT]; // the scenes
    constants::sceneVariables::Scene currentScene; // the current scene

    // buttons
    Button* submenuButton,
            *demoCodeButton;

    /**
     * @brief Initialize the window
     * 
     */
    void initWindow();
    /**
     * @brief Initialize the scenes
     * 
     */
    void initScenes();
    /**
     * @brief Initialize the buttons
     * 
     */
    void init();

public:
    /**
     * @brief Construct a new Window object
     * 
     */
    Window();
    /**
     * @brief Destroy the Window object
     * 
     */
    ~Window() = default;

    /**
     * @brief Check if the window is running
     * 
     * @return true if the window is running
     * @return false if the window is not running
     */
    const bool running() const;

    /**
     * @brief Poll the event
     * 
     */
    void pollEvent();
    /**
     * @brief Update the window
     * 
     */
    void update();
    /**
     * @brief Render the window
     * 
     */
    void render();
};

#endif //VISUALGO_CS162_WINDOW_HPP
