//
// Created by dirii on 28/04/2023.
//

#ifndef VISUALGO_CS162_SQUARE_HPP
#define VISUALGO_CS162_SQUARE_HPP

#include "Constants.hpp"
#include "BaseDraw.hpp"

class Square : BaseDraw{
public:
    enum class Status{
        inactive,
        active,
        chosen,
        hidden
    };

    sf::Font font;

    Square(sf::RenderWindow *window, std::string value, sf::Vector2f position);
    void render() override;

    void setStatus(Status _status);
    void resetColor();
    Status getStatus();

    void setText(std::string _value);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

private:
    sf::RectangleShape square;
    sf::Text label;
    std::string value;
    Status status = Status::inactive;
};

#endif //VISUALGO_CS162_SQUARE_HPP
