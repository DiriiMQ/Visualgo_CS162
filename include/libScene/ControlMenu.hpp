//
// Created by dirii on 14/04/2023.
//

#ifndef VISUALGO_CS162_CONTROLMENU_HPP
#define VISUALGO_CS162_CONTROLMENU_HPP

#include <SFML/Graphics.hpp>
#include "stuff/button.hpp"
#include "stuff/ToStringWithPrecision.hpp"
#include "Constants.hpp"

class ControlMenu {
private:
    sf::RenderWindow* window;

    Button* buttons[constants::ControlMenu::BUTTON_COUNT];
    sf::Font font;
    sf::Text textSpeed;
    float speed;

public:
    enum class StatusCode {
        PREVIOUS,
        PAUSE,
        PLAY,
        NEXT,
        None
    } status;

    explicit ControlMenu(sf::RenderWindow* window);
    ~ControlMenu() = default;

    void pollEvents(sf::Event event, sf::Vector2f mousePosView);
    void update();
    void render();
    void reset();

    ControlMenu::StatusCode getStatus();
    [[nodiscard]] float getSpeed() const;
};

#endif //VISUALGO_CS162_CONTROLMENU_HPP
