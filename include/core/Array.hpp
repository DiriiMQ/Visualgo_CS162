//
// Created by dirii on 28/04/2023.
//

#ifndef VISUALGO_CS162_ARRAY_HPP
#define VISUALGO_CS162_ARRAY_HPP

#include "Random.h"
#include "core/Vector.h"
#include "draw/SquareInfo.hpp"
#include "libScene/Highlighter.hpp"
#include "libScene/ControlMenu.hpp"
#include "EventAnimation.hpp"

class Array : public BaseDraw{
public:
    enum class TypeArray{
        DYNAMIC,
        STATIC
    };

    Array(sf::RenderWindow *window, TypeArray typeArray);
    Array(sf::RenderWindow *window, TypeArray typeArray, int size);
    Array(sf::RenderWindow *window, TypeArray typeArray, std::vector<std::string> values);
    void init(TypeArray typeArray);
    ~Array() = default;
    void render() override;
    void renderHighlighter();
    void update();

    void setSpeed(float speed);
    int findValue(const std::string& value);

    void updateAnimation();
    void resetEvents();

    [[nodiscard]] int getSize() const;
    [[nodiscard]] int getSquaresSize() const;

    void processControlMenu(ControlMenu::StatusCode status);

    // operations of highlighter
    void initHighlighter(int linesCount, const char *codePath);
    void toggleLines(std::vector<int> lines);

    // operations of array
    void createArray(int size);
    void createArray(const std::vector<std::string>& values);
    void allocateSquare(int size, const std::vector<EventAnimation>& listEvents);
    void addSquare(int position, std::string value, const std::vector<EventAnimation>& listEvents);
    void deleteSquare(int position, const std::vector<EventAnimation>& listEvents);
    void updateSquare(int position, std::string value, const std::vector<EventAnimation>& listEvents);
    void searchSquare(const std::vector<EventAnimation>& listEvents);

private:
    sf::Clock clock;
    int chosenNode = 0, deletedNode = -1;
    TypeArray typeArray;

    Vector<SquareInfo*> squares, squaresTemp;
    int size;

    Highlighter* highlighter;

    std::vector<EventAnimation> events;
    int currentEvent = 0;

    float speed, delayTime;
    bool isDelay = false;
};

#endif //VISUALGO_CS162_ARRAY_HPP
