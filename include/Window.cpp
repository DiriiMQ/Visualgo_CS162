//
// Created by dirii on 23/03/2023.
//

#include "Window.hpp"

void Window::init() {
    this->initWindow();
    this->relativeWindow = this->window;

    // init buttons
    this->submenuButton = new Button(
            this->window,
            constants::submenuButtonPos,
            constants::sideButtonSize,
            ">",
            "<",
            15,
            sf::Color::Black,
            constants::normalGray,
            constants::hoverGray,
            constants::clickGray
            );

    this->demoCodeButton = new Button(
            this->window,
            constants::demoCodeButtonPos,
            constants::sideButtonSize,
            "<",
            ">",
            15,
            sf::Color::Black,
            constants::normalGray,
            constants::hoverGray,
            constants::clickGray
            );
}

void Window::initWindow() {
    this->videoMode.width = constants::Width;
    this->videoMode.height = constants::Height;
    this->window = new sf::RenderWindow(
            this->videoMode,
            constants::titleWindow,
            sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(constants::fps);
}

Window::Window() {
    init();
}

const bool Window::running() const {
    return this->window->isOpen();
}

void Window::pollEvent() {
    // event polling
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Q) {
                    std::cout << "You have pressed Q!\n";
                }
                if (this->event.key.code == sf::Keyboard::W) {
                    std::cout << "You have pressed W!\n";
                }
                break;
            default:
                break;
        }

        if (this->submenuButton->pollEvent(this->mousePosView)) {
            std::cout << "You have clicked on submenu button!\n";
        }

        if (this->demoCodeButton->pollEvent(this->mousePosView)) {
            std::cout << "You have clicked on demo code button!\n";
        }
    }
}

void Window::update() {
    this->updateMousePosition();
    this->pollEvent();

    this->submenuButton->update();
    this->demoCodeButton->update();
}

void Window::render() {
    /*
 * clear old frames
 * create objects
 * display it
 */

    this->window->clear(sf::Color::White);

    // drawing game
    this->submenuButton->render();
    this->demoCodeButton->render();

    this->window->display();
}
