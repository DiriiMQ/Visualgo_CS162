//
// Created by dirii on 28/04/2023.
//

#ifndef VISUALGO_CS162_SQUAREINFO_HPP
#define VISUALGO_CS162_SQUAREINFO_HPP

#include "Square.hpp"

class SquareInfo : public BaseDraw {
public:
    SquareInfo(sf::RenderWindow *window, std::string value, sf::Vector2f position);
    ~SquareInfo() = default;
    void update();
    void render() override;

    void setValue(std::string value);
    void setTitle(const std::string& _title);
    void setStatus(Square::Status _status);
    void setPrintPreVal(bool _isPrintPreVal);

    std::string getValue();
    Square::Status getStatus();

    void resetTitle();
    void reset();

private:
    sf::Vector2f position;
    Square* square;
    std::string values[2];
    sf::Text title;

    bool isPrintPreVal;
};

#endif //VISUALGO_CS162_SQUAREINFO_HPP
