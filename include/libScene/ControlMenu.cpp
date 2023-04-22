//
// Created by dirii on 14/04/2023.
//

#include "ControlMenu.hpp"

ControlMenu::ControlMenu(sf::RenderWindow *window) {
    this->window = window;

    for (int i = 0; i < constants::ControlMenu::BUTTON_COUNT; ++i) {
        buttons[i] = new Button(
                this->window,
                constants::ControlMenu::buttonPos[i],
                constants::ControlMenu::buttonSize,
                constants::ControlMenu::BUTTON_NAMES[i],
                constants::ControlMenu::BUTTON_NAMES[i],
                constants::ControlMenu::BUTTON_NAME_SIZE,
                sf::Color::Black,
                constants::normalGray,
                constants::hoverGray,
                constants::clickGray
                );
    }

    this->font.loadFromFile(constants::fontPath);
    this->textSpeed.setFont(font);
    this->textSpeed.setString(to_string_with_precision(this->speed));
    this->textSpeed.setCharacterSize(constants::ControlMenu::TEXT_SIZE);
    this->textSpeed.setFillColor(sf::Color::Black);
    this->textSpeed.setOrigin(
            this->textSpeed.getLocalBounds().width / 2.0f,
            this->textSpeed.getLocalBounds().height / 2.0f
            );
    this->textSpeed.setPosition(
            constants::ControlMenu::buttonPos[3].x + constants::ControlMenu::buttonSize.x * 2,
            constants::ControlMenu::buttonPos[3].y + constants::ControlMenu::buttonSize.y / 2.0f
            );

    this->status = StatusCode::None;
    this->speed = 1;
}

void ControlMenu::pollEvents(sf::Event event, sf::Vector2f mousePosView) {
    for (int i = 0; i < constants::ControlMenu::BUTTON_COUNT; ++i) {
        if (buttons[i]->pollEvent(mousePosView)) {
            switch (i) {
                case 0:
                    this->status = StatusCode::PREVIOUS;
                    break;
                case 1:
                    if (this->status == StatusCode::PLAY)
                        this->status = StatusCode::PAUSE;
                    else
                        this->status = StatusCode::PLAY;
                    break;
                case 2:
                    this->status = StatusCode::NEXT;
                    break;
                case 3:
                    if (this->speed > 0.25)
                        this->speed -= 0.25;
                    break;
                case 4:
                    if (this->speed < 2)
                        this->speed += 0.25;
                    break;
                default:
                    this->status = StatusCode::None;
                    break;
            }
        }
    }
}

void ControlMenu::update() {
    for (auto &button : buttons) {
        button->update();
    }
    this->textSpeed.setString(to_string_with_precision(this->speed));
}

void ControlMenu::render() {
    for (auto &button : buttons) {
        button->render();
    }
    this->window->draw(this->textSpeed);
}

ControlMenu::StatusCode ControlMenu::getStatus() {
    ControlMenu::StatusCode temp = this->status;
    if (this->status == StatusCode::PREVIOUS || this->status == StatusCode::NEXT)
        this->status = StatusCode::PAUSE;
    return temp;
}

float ControlMenu::getSpeed() const {
    return this->speed;
}

void ControlMenu::reset() {
    this->status = StatusCode::None;
}
