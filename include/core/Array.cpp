//
// Created by dirii on 28/04/2023.
//

#include "Array.hpp"

#include <utility>

Array::Array(sf::RenderWindow *window, TypeArray typeArray) : BaseDraw(window) {
    this->init(typeArray);
    this->createArray(0);
}

Array::Array(sf::RenderWindow *window, Array::TypeArray typeArray, int size) : BaseDraw(window)  {
    this->init(typeArray);
    this->createArray(size);
}

Array::Array(sf::RenderWindow *window, Array::TypeArray typeArray, std::vector<std::string> values) : BaseDraw(window)  {
    this->init(typeArray);
    this->createArray(std::move(values));
}

void Array::init(Array::TypeArray typeArray) {
    this->typeArray = typeArray;
    this->highlighter = nullptr;
    this->delayTime = constants::LinkedList::DELAY_TIME;
    this->size = 0;
}

void Array::render() {
    for (auto &square : this->squares) {
        square->render();
    }
    for (auto &square: this->squaresTemp) {
        square->render();
    }
}

void Array::renderHighlighter() {
    if (this->highlighter)
        this->highlighter->render();
}

void Array::update() {
    if ((int)this->events.size() && (this->isDelay or this->clock.getElapsedTime().asSeconds() > this->delayTime / this->speed))
        this->updateAnimation();
    this->isDelay = false;
}

void Array::setSpeed(float _speed) {
    this->speed = _speed;
}

int Array::findValue(const std::string &value) {
    for (int i = 0; i < this->size; i++) {
        if (this->squares[i]->getValue() == value)
            return i;
    }
    return this->size;
}

int Array::getSize() const {
    return this->size;
}

void Array::processControlMenu(ControlMenu::StatusCode status) {
    if (this->clock.getElapsedTime().asSeconds() < this->delayTime / this->speed)
        return;
    switch (status){
        case ControlMenu::StatusCode::PREVIOUS:
            if (this->currentEvent > 0)
                --this->currentEvent;
            break;
        case ControlMenu::StatusCode::PAUSE:
//            std::cout << "PAUSE" << std::endl;
            break;
        case ControlMenu::StatusCode::PLAY:
            if (this->currentEvent + 1 < this->events.size()) {
                this->isDelay = true;
                this->clock.restart();
            }
        case ControlMenu::StatusCode::NEXT:
            if (this->currentEvent + 1 < this->events.size())
                ++this->currentEvent;
            break;
        default:
            break;
    }
}

void Array::initHighlighter(int linesCount, const char *codePath) {
    delete this->highlighter;
    this->highlighter = new Highlighter(
            this->window,
            linesCount,
            codePath
    );
}

void Array::toggleLines(std::vector<int> lines) {
    this->highlighter->toggle(std::move(lines));
}

void Array::updateAnimation() {
    if (this->squares.empty())
        return;

    for (auto &square : this->squares) {
        square->reset();
    }
    for (auto &square : this->squaresTemp) {
        square->reset();
    }

    EventAnimation &event = this->events[this->currentEvent];
    for (int i = 0; i < event.eventSquares.size(); ++i) {
        this->squares[i]->setStatus(event.eventSquares[i].status);
        this->squares[i]->setPrintPreVal(event.eventSquares[i].isPrintPreVal);
        this->squares[i]->setTitle(event.eventSquares[i].title);
    }
    for (int i = 0; i < event.eventSquaresTemp.size(); ++i) {
        this->squaresTemp[i]->setStatus(event.eventSquaresTemp[i].status);
        this->squaresTemp[i]->setPrintPreVal(event.eventSquaresTemp[i].isPrintPreVal);
        this->squaresTemp[i]->setTitle(event.eventSquaresTemp[i].title);
    }

    if (this->highlighter)
        this->highlighter->toggle(event.lines);

    for (auto &square : this->squares) {
        square->update();
    }
    for (auto &square : this->squaresTemp) {
        square->update();
    }
}

void Array::resetEvents() {
    delete this->highlighter;
    this->highlighter = nullptr;
    this->currentEvent = 0;
    this->events.clear();
    this->squaresTemp.clear();

    while (!this->squares.empty() && this->squares.back()->getStatus() == Square::Status::hidden)
        this->squares.pop_back();

    for (int i = 0; i < this->size; ++i)
        this->squares[i]->setStatus(Square::Status::active);
    for (int i = this->size; i < this->squares.size(); ++i)
        this->squares[i]->setStatus(Square::Status::inactive);
    if (this->size)
        this->squares[this->size - 1]->setTitle("n");
}

void Array::createArray(int _size) {
    this->resetEvents();
    this->size = _size;
    for (auto &square : this->squares)
        delete square;
    this->squares.resize(this->size);
    for (int i = 0; i < this->size; ++i) {
        this->squares[i] = new SquareInfo(
                this->window,
                std::to_string(Random::randomInt(0, 99)),
                sf::Vector2f(
                        constants::Square::originNode.x + static_cast<float>(i) * constants::Square::offsetX,
                        constants::Square::originNode.y
                        )
        );
        this->squares[i]->setStatus(Square::Status::active);
    }
    if (this->size)
        this->squares[this->size - 1]->setTitle("n");
}

void Array::createArray(const std::vector<std::string>& values) {
    this->resetEvents();
    this->size = (int)values.size();
    for (auto &square : this->squares)
        delete square;
    this->squares.resize(this->size);
    for (int i = 0; i < this->size; ++i) {
        this->squares[i] = new SquareInfo(
                this->window,
                values[i],
                sf::Vector2f(
                        constants::Square::originNode.x + static_cast<float>(i) * constants::Square::offsetX,
                        constants::Square::originNode.y
                )
        );
        this->squares[i]->setStatus(Square::Status::active);
    }
    if (this->size)
        this->squares[this->size - 1]->setTitle("n");
}

int Array::getSquaresSize() const {
    return (int)this->squares.size();
}

void Array::allocateSquare(int _size, const std::vector<EventAnimation> &listEvents) {
    this->squaresTemp.resize(_size);
//    this->squares.resize();

    while (this->squares.size() < _size)
        this->squares.push_back(new SquareInfo(
                this->window,
                "",
                sf::Vector2f(
                        constants::Square::originNode.x + static_cast<float>(this->squares.size()) * constants::Square::offsetX,
                        constants::Square::originNode.y
                )
        ));

    for (int i = 0; i < _size; ++i) {
        this->squaresTemp[i] = new SquareInfo(
                this->window,
                "",
                sf::Vector2f(
                        constants::Square::originNode.x + static_cast<float>(i) * constants::Square::offsetX,
                        constants::Square::originNode.y + constants::Square::offsetY
                )
        );
        this->squaresTemp[i]->setValue(this->squares[i]->getValue());
    }

    this->size = std::min(this->size, _size);
    this->currentEvent = 0;
    this->events = listEvents;
}

void Array::addSquare(int position, std::string value, const std::vector<EventAnimation> &listEvents) {
    if (position < 0 || position > this->size)
        return;

    ++this->size;
    if (this->typeArray == TypeArray::DYNAMIC && this->size > this->getSquaresSize()) {
        this->squares.push_back(new SquareInfo(
                this->window,
                "",
                sf::Vector2f(
                        constants::Square::originNode.x + static_cast<float>(this->getSquaresSize()) * constants::Square::offsetX,
                        constants::Square::originNode.y
                )
        ));
        this->squaresTemp.resize(this->size);
        for (int i = 0; i < this->size; ++i) {
            this->squaresTemp[i] = new SquareInfo(
                    this->window,
                    "",
                    sf::Vector2f(
                            constants::Square::originNode.x + static_cast<float>(i) * constants::Square::offsetX,
                            constants::Square::originNode.y + constants::Square::offsetY
                    )
            );
            this->squaresTemp[i]->setValue(this->squares[i]->getValue());
        }
    }

    if (size > this->getSquaresSize())
        --this->size;

    for (int i = this->size - 1; i > position; --i)
        this->squares[i]->setValue(this->squares[i - 1]->getValue());
    this->squares[position]->setValue(std::move(value));
    for (int i = 0; i < position; ++i)
        this->squares[i]->setValue(this->squares[i]->getValue());

    this->currentEvent = 0;
    this->events = listEvents;
}

void Array::deleteSquare(int position, const std::vector<EventAnimation> &listEvents) {
    if (position < 0 || position >= this->size)
        return;

    --this->size;

    for (int i = position; i < this->size; ++i)
        this->squares[i]->setValue(this->squares[i + 1]->getValue());
    for (int i = 0; i < position; ++i)
        this->squares[i]->setValue(this->squares[i]->getValue());
    this->squares[this->size]->setValue(this->squares[this->size]->getValue());

    this->currentEvent = 0;
    this->events = listEvents;
}

void Array::updateSquare(int position, std::string value, const std::vector<EventAnimation> &listEvents) {
    if (position < 0 || position >= this->size)
        return;

    this->squares[position]->setValue(std::move(value));

    this->currentEvent = 0;
    this->events = listEvents;
}

void Array::searchSquare(const std::vector<EventAnimation> &listEvents) {
    this->currentEvent = 0;
    this->events = listEvents;
}
